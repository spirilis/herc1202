/*
 * herc1202.h
 *
 *  Created on: Aug 9, 2013
 *      Author: spirilis
 */

#ifndef HERC1202_H_
#define HERC1202_H_

/* Nokia 1202 driver for TI Hercules TMS570 and RM4
 * HALCoGen API required
 */
#include "spi.h"
#include "FreeRTOS.h"
#include "os_queue.h"
#include "os_semphr.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Driver configuration - Which SPI are we using? */
#define HERC1202_SPIREG spiREG1
// SPI chip select pin (e.g. SPIxCS0, SPIxCS1, etc; specify as number)
#define HERC1202_SPICSEL 1
// SPI data format specification (0-3); typically one configured for 8MHz 9-bit mode 0.
#define HERC1202_DATAFMT SPI_FMT_3
// Max # of outstanding requests to the driver task
#define HERC1202_QUEUE_LENGTH 4
// # characters per tab stop
#define HERC1202_TAB_SPACING 4



/* Internal & communication queue data-types */
/* Handle to the LCD driver */
typedef struct {
	xQueueHandle request_queue;
	xSemaphoreHandle notifier;  /* Binary semaphore used to allow client to block
								 * until driver task has completed its outstanding request.
								 */
	uint8_t async;
} Herc1202HandleStruct;

typedef Herc1202HandleStruct * Herc1202Handle;

/* LCD write or config request */
typedef struct {
	void *buffer;
	int len;
	int reqtype;
	uint8_t cmdargs[4];
	xSemaphoreHandle notifier;
} Herc1202RequestStruct;

typedef Herc1202RequestStruct * Herc1202Request;

enum Herc1202 {
	Herc1202_WRITE=0,
	Herc1202_RAWCMD=1,
	Herc1202_PUTCHAR=2,
	Herc1202_CLEAR=3,
	Herc1202_CURSOR=4,
	Herc1202_POWERSAVE=5,
	Herc1202_CONTRAST=6,
	Herc1202_INVERT=7,
	Herc1202_REFRESHRATE=8
};

/* Queue used to communicate with driver--not for general use, it's presented internally by helper functions */
extern xQueueHandle Herc1202RequestQueue;

/* Function prototypes */
Herc1202Handle Herc1202_Open();  // Create a handle with a unique semaphore for synchronous blocking
portBASE_TYPE Herc1202_Async(Herc1202Handle, uint8_t async_onoff); // Declare I/O calls synchronous or asynchronous
portBASE_TYPE Herc1202_Wait(Herc1202Handle, uint8_t do_block); // Test semaphore for completion (or block until)
portBASE_TYPE Herc1202_Close(Herc1202Handle); // Destroy notifier semaphore and handle

portBASE_TYPE Herc1202_Command(Herc1202Handle, int reqtype, void *buffer, void *command, int len); // Used internally
portBASE_TYPE Herc1202_Write(Herc1202Handle, uint8_t x, uint8_t y, void *buffer, int len); // Write graphics
portBASE_TYPE Herc1202_Puts(Herc1202Handle, void *buffer); // Write null-terminated string using font/terminal semantics
portBASE_TYPE Herc1202_Clear(Herc1202Handle); // Clear screen, position cursor at 0,0
portBASE_TYPE Herc1202_Powersave(Herc1202Handle, uint8_t onoff); // Place display into <10uA low power mode
portBASE_TYPE Herc1202_SetXY(Herc1202Handle, uint8_t x, uint8_t y); // Change cursor position
portBASE_TYPE Herc1202_Contrast(Herc1202Handle, uint8_t contrast); // Set LCD contrast; 0-31
portBASE_TYPE Herc1202_Invert(Herc1202Handle, uint8_t onoff); // Invert display pixel scheme
portBASE_TYPE Herc1202_Refreshrate(Herc1202Handle, uint8_t rate); // Change LCD refresh rate

portBASE_TYPE Herc1202_Init(xSemaphoreHandle spiMutex); // Issued in main() to create the driver task


#endif /* HERC1202_H_ */
