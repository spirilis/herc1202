/** @file sys_main.c 
*   @brief Application main file
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_timer.h"
#include <stdlib.h>
#include <stdint.h>
#include "herc1202.h"
#include "spi.h"
#include "sci.h"
#include "gio.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
xSemaphoreHandle spiarb;
void LCD_test(void *);

/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	spiInit();
	spiarb = xSemaphoreCreateMutex();
	sciInit();
	gioInit();

	Herc1202_Init(spiarb);
	xTaskCreate(LCD_test, (const signed char*)"LCDWRITER", 256, NULL, 0, NULL);
	sciSend(scilinREG, 21, (uint8_t*)"Starting scheduler:\r\n");
	vTaskStartScheduler();
	while(1) ;
/* USER CODE END */
}

/* USER CODE BEGIN (4) */

void LCD_test(void *pvParameters)
{
	Herc1202Handle lcd;

	// Enable LCD backlight (GIOA6 ~ P2.5, default pin for backlight on The 1202 BoosterPack.
	gioSetBit(gioPORTA, 6, 1);

	lcd = Herc1202_Open();
	// herc1202_font5x7.c has the TI logo glyph loaded into char# 0x81, 0x82 (left half/right half)
	Herc1202_Puts(lcd, "\x81\x82 MSP430 MCU\n");
	Herc1202_Puts(lcd, "Power Players\n\n");
	Herc1202_Puts(lcd, "    PRESENTS\n\n");
	Herc1202_Puts(lcd, "Hercules TMS570\n");
	Herc1202_Puts(lcd, "LaunchPad w/\n");
	Herc1202_Puts(lcd, "   FreeRTOS!");
	while(1)
		taskYIELD();
}


/* USER CODE END */
