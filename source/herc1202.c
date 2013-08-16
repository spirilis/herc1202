/*
 * herc1202.c
 *
 *  Created on: Aug 9, 2013
 *      Author: spirilis
 *
 *  Nokia 1202 driver for FreeRTOS
 *  TI Hercules TMS570 and RM4
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_portable.h"
#include "os_timer.h"
#include "herc1202.h"
#include "ste2007.h"
#include <stdint.h>
#include <string.h>

/* Global variables, extern flash-stored arrays and internal/private functions. */
xQueueHandle Herc1202RequestQueue;
static uint8_t _x, _y;
void Herc1202_DriverTask(void *);
void Herc1202_DriverTaskWorker_Command(spiDAT1_t *, uint8_t, uint8_t, void *);
void Herc1202_DriverTask_Init(spiDAT1_t *);
void Herc1202_DriverTask_Writechar(spiDAT1_t *, uint8_t);
void Herc1202_DriverTask_SetXY(spiDAT1_t *, uint8_t, uint8_t);
void Herc1202_DriverTask_Putchar(spiDAT1_t *, uint8_t);

extern const uint8_t Herc1202_font_5x7[][6];
extern const uint16_t Herc1202_ClearBuffer[];

/* Initialize task & queue structure--can be run during main() before vTaskStartScheduler() */
portBASE_TYPE Herc1202_Init(xSemaphoreHandle spiMutex)
{
	/* Create the common request queue */
	Herc1202RequestQueue = xQueueCreate(HERC1202_QUEUE_LENGTH, sizeof(Herc1202RequestStruct));
	if (!Herc1202RequestQueue) {
		return pdFALSE;
	}

	/* Start the Driver Task. */
	if (pdPASS != xTaskCreate(Herc1202_DriverTask, (signed char*)"HERC1202_SPI", 256, (void*)spiMutex, configMAX_PRIORITIES-2, NULL)) {
		vQueueDelete(Herc1202RequestQueue);
		return pdFALSE;
	}

	return pdTRUE;
}

void Herc1202_DriverTask(void *pvParameters)
{
	Herc1202RequestStruct req;
	xSemaphoreHandle spiMutex;
	spiDAT1_t spicfg;
	long i;
	uint16_t *hugebuf;
	uint8_t bytebuf;

	//
	spiMutex = (xSemaphoreHandle) pvParameters;

	spicfg.CSNR = HERC1202_SPICSEL;
	spicfg.CS_HOLD = 0;
	spicfg.DFSEL = HERC1202_DATAFMT;
	spicfg.WDEL = 0;

	// Initialize the Nokia 1202 LCD display
	xSemaphoreTake(spiMutex, portMAX_DELAY);
	Herc1202_DriverTask_Init(&spicfg);
	xSemaphoreGive(spiMutex);

	while(1) {
		xQueueReceive(Herc1202RequestQueue, &req, portMAX_DELAY);  // Wait indefinitely for incoming data
		// Wait for SPI bus to become available
		xSemaphoreTake(spiMutex, portMAX_DELAY);

		// Process request
		switch (req.reqtype) {
			case Herc1202_WRITE:
				/* This is meant for writing graphics; X,Y location must be stuffed in the first 2 bytes.
				 * X location is assumed to be character position (X is multiplied by 6 to get actual LCD column).
				 * Data following that is direct pixel information.
				 *
				 * After X,Y location we assume to have a 32-bit pointer to the actual data buffer.
				 */
				if (req.len < 1)
					break;
				Herc1202_DriverTask_SetXY(&spicfg, req.cmdargs[0], req.cmdargs[1]);

				hugebuf = (uint16_t*)pvPortMalloc((req.len) * sizeof(uint16_t));
				for (i=0; i < req.len; i++) {
					hugebuf[i] = 0x0100 | ((uint8_t*)req.buffer)[i];;
				}
				spicfg.CS_HOLD = 1;
				spiTransmitData(HERC1202_SPIREG, &spicfg, req.len, hugebuf);
				spicfg.CS_HOLD = 0;
				vPortFree(hugebuf);
				Herc1202_DriverTask_SetXY(&spicfg, _x, _y);
				break;
			case Herc1202_RAWCMD:
				hugebuf = (uint16_t*)pvPortMalloc(req.len * sizeof(uint16_t));
				for (i=0; i < req.len; i++) {
					hugebuf[0] = ((uint8_t*)req.buffer)[i];
				}
				spicfg.CS_HOLD = 1;
				spiTransmitData(HERC1202_SPIREG, &spicfg, req.len, hugebuf);
				spicfg.CS_HOLD = 0;
				vPortFree(hugebuf);
				break;
			case Herc1202_PUTCHAR:
				for (i=0; i < req.len; i++) {
					Herc1202_DriverTask_Putchar(&spicfg, ((uint8_t*)req.buffer)[i]);
				}
				break;
			case Herc1202_CLEAR:
				bytebuf = 0;
				// Reset cursor to 0,0
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_LINE, 0, &bytebuf);
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_COLMSB, 0, &bytebuf);
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_COLLSB, 0, &bytebuf);
				// Clear framebuffer
				spicfg.CS_HOLD = 1;
				spiTransmitData(HERC1202_SPIREG, &spicfg, 16*6*9, (uint16_t*)Herc1202_ClearBuffer);
				spicfg.CS_HOLD = 0;
				// Verify cursor is at 0,0
				_x = _y = 0;
				Herc1202_DriverTask_SetXY(&spicfg, _x, _y);
				Herc1202_DriverTask_Writechar(&spicfg, 0x80);
				Herc1202_DriverTask_SetXY(&spicfg, _x, _y);
				break;
			case Herc1202_CURSOR:
				Herc1202_DriverTask_Writechar(&spicfg, ' ');
				_x = req.cmdargs[0];
				_y = req.cmdargs[1];
				Herc1202_DriverTask_SetXY(&spicfg, _x, _y);
				Herc1202_DriverTask_Writechar(&spicfg, 0x80);
				Herc1202_DriverTask_SetXY(&spicfg, _x, _y);
				break;
			case Herc1202_POWERSAVE:
				// Powersave mode is ONOFF=0, DPYALLPTS=1 (<10uA draw)
				bytebuf = req.cmdargs[0] & STE2007_MASK_DPYALLPTS;
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_DPYALLPTS, 0, &bytebuf);
				bytebuf = ~(req.cmdargs[0]) & STE2007_MASK_ONOFF;
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_ONOFF, 0, &bytebuf);
				break;
			case Herc1202_CONTRAST:
				// Value should be 0-31
				bytebuf = req.cmdargs[0] & STE2007_MASK_ELECTVOL;
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_ELECTVOL, 0, &bytebuf);
				break;
			case Herc1202_INVERT:
				bytebuf = req.cmdargs[0] & STE2007_MASK_DPYREV;
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_DPYREV, 0, &bytebuf);
				break;
			case Herc1202_REFRESHRATE:
				switch (req.cmdargs[0]) {
					case 80:
						bytebuf = 0;
						break;
					case 75:
						bytebuf = 1;
						break;
					case 70:
						bytebuf = 2;
						break;
					default:
						bytebuf = 3;
						break;
				}
				Herc1202_DriverTaskWorker_Command(&spicfg, STE2007_CMD_REFRESHRATE, 1, &bytebuf);
				break;
		}

		// Release SPI bus
		xSemaphoreGive(spiMutex);

		// Notify calling task of completion if applicable
		if (req.notifier != NULL) {
			xSemaphoreGive(req.notifier);  // notifier = binary semaphore
			//sciSend(scilinREG, 30, "Released notifier semaphore.\r\n");
		}
	}
}


static volatile uint8_t _initDelay;

void Herc1202_DriverTask_Init_EndDelay(xTimerHandle xTimer)
{
	_initDelay = 0;
}

void Herc1202_DriverTask_Init(spiDAT1_t *spicfg)
{
	xTimerHandle prvTimer;
	uint8_t bytebuf;

	// Wait at least 100ms for STE2007 controller to wake up
	prvTimer = xTimerCreate((signed char*)"STE2007_INIT", 100/portTICK_RATE_MS, pdFALSE, NULL, Herc1202_DriverTask_Init_EndDelay);
	_initDelay = 1;
	xTimerStart(prvTimer, portMAX_DELAY);

	while (_initDelay)
		taskYIELD();
	xTimerDelete(prvTimer, 20/portTICK_RATE_MS);

	// Carry out all init processes
	bytebuf = 0;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_RESET, 0, &bytebuf);
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_DPYALLPTS, 0, &bytebuf);
	bytebuf = 7;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_PWRCTL, 0, &bytebuf);
	bytebuf = 1;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_ONOFF, 0, &bytebuf);
	bytebuf = 0;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_COMDIR, 0, &bytebuf);
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_SEGMENTDIR, 0, &bytebuf);
	bytebuf = 16;  // default contrast = 16
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_ELECTVOL, 0, &bytebuf);

	/* Clear */
	bytebuf = 0;
	// Reset cursor to 0,0
	Herc1202_DriverTask_SetXY(spicfg, 0, 0);
	// Clear framebuffer
	spicfg->CS_HOLD = 1;
	spiTransmitData(HERC1202_SPIREG, spicfg, 16*6*9, (uint16_t*)Herc1202_ClearBuffer);
	spicfg->CS_HOLD = 0;
	/* Done clear */

	bytebuf = 3;  // Default refreshrate = 60Hz
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_REFRESHRATE, 1, &bytebuf);
	bytebuf = 0;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_CHARGEPUMP, 1, &bytebuf);
	bytebuf = 6;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_SETBIAS, 0, &bytebuf);
	bytebuf = 0;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_VOP, 1, &bytebuf);
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_DPYREV, 0, &bytebuf);

	// Verify cursor is at 0,0
	_x = _y = 0;
	Herc1202_DriverTask_SetXY(spicfg, _x, _y);
	Herc1202_DriverTask_Writechar(spicfg, 0x80);
	Herc1202_DriverTask_SetXY(spicfg, _x, _y);
}

void Herc1202_DriverTask_SetXY(spiDAT1_t *spicfg, uint8_t x, uint8_t y)
{
	uint8_t spibuf;

	x *= 6;
	spibuf = y;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_LINE, 0, &spibuf);
	spibuf = (x >> 4) & STE2007_MASK_COLMSB;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_COLMSB, 0, &spibuf);
	spibuf = x & STE2007_MASK_COLLSB;
	Herc1202_DriverTaskWorker_Command(spicfg, STE2007_CMD_COLLSB, 0, &spibuf);
}

/* WriteChar handles the font; writes a single character in place based on the font, doing a multi-byte
 * SPI call with CS_HOLD=1.
 */
void Herc1202_DriverTask_Writechar(spiDAT1_t *spicfg, uint8_t c)
{
	uint16_t spibuf[6];
	long i;

	for (i=0; i < 6; i++) {
		spibuf[i] = 0x0100 | Herc1202_font_5x7[c-0x20][i];
	}
	spicfg->CS_HOLD = 1;
	spiTransmitData(HERC1202_SPIREG, spicfg, 6, spibuf);
	spicfg->CS_HOLD = 0;
}

/* Putchar processes the terminal concept, including \n \t and \b control characters.
 */
void Herc1202_DriverTask_Putchar(spiDAT1_t *spicfg, uint8_t c)
{
	/* Note: High-bit characters are valid in this implementation, and there are glyphs which may correspond.
	 * 0x80 is the cursor, 0x81+0x82 comprise the TI logo, etc; you may customize herc1202_font5x7.c to change these.
	 */

	if (c >= 0x20) {
		Herc1202_DriverTask_Writechar(spicfg, c);
		_x++;
	} else {
		// Process control character
		switch (c) {
			case '\n':
				// Erase cursor at present position before moving it
				Herc1202_DriverTask_Writechar(spicfg, ' ');
				_x = 0;
				_y++;
				Herc1202_DriverTask_SetXY(spicfg, _x, _y);
				break;
			case '\t':
				// Erase cursor at present position before moving it
				Herc1202_DriverTask_Writechar(spicfg, ' ');
				if (_x % HERC1202_TAB_SPACING == 0)
					_x += HERC1202_TAB_SPACING;
				else
					_x += _x % HERC1202_TAB_SPACING;
				Herc1202_DriverTask_SetXY(spicfg, _x, _y);
				break;
			case '\b':
				if (_x) {  // Nothing happens if @ beginning of line
					_x--;
					// Otherwise, previous character gets erased.
					Herc1202_DriverTask_SetXY(spicfg, _x, _y);
					Herc1202_DriverTask_Writechar(spicfg, ' ');
					Herc1202_DriverTask_SetXY(spicfg, _x, _y);
				}
				break;
		}
	}

	if (_x >= 16) {
		// Shift down one row
		_y++;
		_x = 0;
		Herc1202_DriverTask_SetXY(spicfg, _x, _y);
	}

	if (_y >= 8) {
		_y = 0;
		Herc1202_DriverTask_SetXY(spicfg, _x, _y);
	}

	Herc1202_DriverTask_Writechar(spicfg, 0x80);
	Herc1202_DriverTask_SetXY(spicfg, _x, _y);
}

void Herc1202_DriverTaskWorker_Command(spiDAT1_t *spicfg, uint8_t cmd, uint8_t is_compound, void *data)
{
	uint16_t spibuf;
	uint32_t spibuf32;

	if (is_compound) {
		spicfg->CS_HOLD = 1;
		spibuf32 = (cmd << 16) | ((uint8_t*)data)[0];
		spiTransmitData(HERC1202_SPIREG, spicfg, 2, (uint16_t*)&spibuf32);
		spicfg->CS_HOLD = 0;
	} else {
		spibuf = cmd | ((uint8_t*)data)[0];
		spiTransmitData(HERC1202_SPIREG, spicfg, 1, &spibuf);
	}
}






/* Client library */
Herc1202Handle Herc1202_Open()
{
	xSemaphoreHandle notifier;
	Herc1202Handle handle;

	/* Allocate a Herc1202Handle, allocate a binary semaphore for completion notifications, then
	 * pass it back to the caller so they can use it with the rest of the client I/O functions.
	 */
	handle = (Herc1202Handle) pvPortMalloc(sizeof(Herc1202HandleStruct));
	handle->request_queue = Herc1202RequestQueue;
	vSemaphoreCreateBinary(notifier);
	xSemaphoreTake(notifier, 0);
	handle->notifier = notifier;
	handle->async = 0;  // Defaults to blocking-mode

	return handle;
}

portBASE_TYPE Herc1202_Close(Herc1202Handle handle)
{
	/* Not much to do, just deallocate the binary semaphore & handle. */
	if (handle == NULL)
		return pdFALSE;  // Invalid argument!
	if (handle->notifier)
		vSemaphoreDelete(handle->notifier);
	vPortFree(handle);
	return pdTRUE;
}

portBASE_TYPE Herc1202_Async(Herc1202Handle handle, uint8_t async_onoff)
{
	if (handle == NULL)
		return pdFALSE;

	handle->async = async_onoff & 0x01;
	return pdTRUE;
}

portBASE_TYPE Herc1202_Wait(Herc1202Handle handle, uint8_t do_block)
{
	if (handle == NULL || handle->notifier == NULL)
		return pdFALSE;

	if (do_block)
		return xSemaphoreTake(handle->notifier, portMAX_DELAY);
	else
		return xSemaphoreTake(handle->notifier, 0);
}

// Marshal simple commands over to the driver task.
portBASE_TYPE Herc1202_Command(Herc1202Handle drvh, int reqtype, void *buffer, void *commandbuf, int len)
{
	Herc1202RequestStruct curreq;

	if (drvh == NULL || (buffer == NULL && commandbuf == NULL && len != 0))
		return pdFALSE;

	// Prepare request (drvh->curreq is a preallocated buffer to contain this request)
	curreq.notifier = drvh->notifier;
	curreq.buffer = buffer;
	curreq.len = len;
	curreq.reqtype = reqtype;
	if (commandbuf != NULL) {
		if (buffer == NULL)
			memcpy(curreq.cmdargs, commandbuf, len);
		else
			memcpy(curreq.cmdargs, commandbuf, 4);
	}

	// Add to I/O queue, fail if queue is full; don't wait.
	if (xQueueSendToBack(drvh->request_queue, &curreq, 0) != pdPASS) {
		return pdFALSE;
	}

	// Implement non-async blocking before returning.
	if (drvh->async == 0) {
		return Herc1202_Wait(drvh, 1);
	}
	// Otherwise the user will have to issue Herc1202_Wait() manually to check when it's complete.
	return pdTRUE;
}

// Pretty much all these commands boil down to a single Herc1202_Command() function.
portBASE_TYPE Herc1202_Write(Herc1202Handle drvh, uint8_t x, uint8_t y, void *buffer, int len)
{
	uint8_t xy[4];

	if (drvh == NULL || (buffer == NULL && len != 0))
		return pdFALSE;

	xy[0] = x;
	xy[1] = y;
	return Herc1202_Command(drvh, Herc1202_WRITE, buffer, &xy, len);
}

portBASE_TYPE Herc1202_Puts(Herc1202Handle drvh, void *buffer)
{
	if (drvh == NULL || buffer == NULL)
		return pdFALSE;

	return Herc1202_Command(drvh, Herc1202_PUTCHAR, buffer, NULL, strlen((const char*)buffer));
}

portBASE_TYPE Herc1202_SetXY(Herc1202Handle drvh, uint8_t x, uint8_t y)
{
	uint8_t xy[2];

	if (drvh == NULL)
		return pdFALSE;

	xy[0] = x;
	xy[1] = y;
	return Herc1202_Command(drvh, Herc1202_CURSOR, NULL, &xy, 2);
}

portBASE_TYPE Herc1202_Clear(Herc1202Handle drvh)
{
	if (drvh == NULL)
		return pdFALSE;

	return Herc1202_Command(drvh, Herc1202_CLEAR, NULL, NULL, 0);
}

portBASE_TYPE Herc1202_Powersave(Herc1202Handle drvh, uint8_t onoff)
{
	uint8_t val;

	if (drvh == NULL)
		return pdFALSE;

	val = onoff;
	return Herc1202_Command(drvh, Herc1202_POWERSAVE, NULL, &val, 1);
}

portBASE_TYPE Herc1202_Contrast(Herc1202Handle drvh, uint8_t contrast)
{
	uint8_t val;

	if (drvh == NULL)
		return pdFALSE;

	val = contrast;
	return Herc1202_Command(drvh, Herc1202_CONTRAST, NULL, &val, 1);
}

portBASE_TYPE Herc1202_Invert(Herc1202Handle drvh, uint8_t onoff)
{
	uint8_t val;

	if (drvh == NULL)
		return pdFALSE;

	val = onoff;
	return Herc1202_Command(drvh, Herc1202_INVERT, NULL, &val, 1);
}

portBASE_TYPE Herc1202_Refreshrate(Herc1202Handle drvh, uint8_t refreshrate)
{
	uint8_t val;

	if (drvh == NULL)
		return pdFALSE;

	val = refreshrate;
	return Herc1202_Command(drvh, Herc1202_REFRESHRATE, NULL, &val, 1);
}
