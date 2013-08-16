/*
    FreeRTOS V7.4.0 - Copyright (C) 2013 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */

#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#if configUSE_TIMERS == 1
	#include "os_timer.h"
#endif

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*----------------------------------------------------------------------------*/

/* Set the privilege level to user mode if xRunningPrivileged is false.  */
/* TCJ: check must be against zero, see prvRaisePrivilege in portASM.asm */
#define portRESET_PRIVILEGE( xRunningPrivileged ) if( xRunningPrivileged == 0 ) portSWITCH_TO_USER_MODE()


/*----------------------------------------------------------------------------*/
#pragma SWI_ALIAS(prvRaisePrivilege, 1);
extern portBASE_TYPE prvRaisePrivilege( void );

/*----------------------------------------------------------------------------*/

signed portBASE_TYPE MPU_xTaskGenericCreate( pdTASK_CODE pvTaskCode, const signed char * const pcName, unsigned short usStackDepth, void *pvParameters, unsigned portBASE_TYPE uxPriority, xTaskHandle *pxCreatedTask, portSTACK_TYPE *puxStackBuffer, const xMemoryRegion * const xRegions )
{
	signed portBASE_TYPE xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskGenericCreate( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, puxStackBuffer, xRegions );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/


void MPU_vTaskAllocateMPURegions( xTaskHandle xTask, const xMemoryRegion * const xRegions )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	vTaskAllocateMPURegions( xTask, xRegions );
	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/


#if ( INCLUDE_vTaskDelete == 1 )
	void MPU_vTaskDelete( xTaskHandle pxTaskToDelete )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskDelete( pxTaskToDelete );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskDelayUntil == 1 )
	void MPU_vTaskDelayUntil( portTickType * const pxPreviousWakeTime, portTickType xTimeIncrement )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskDelay == 1 )
	void MPU_vTaskDelay( portTickType xTicksToDelay )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskDelay( xTicksToDelay );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_uxTaskPriorityGet == 1 )
	unsigned portBASE_TYPE MPU_uxTaskPriorityGet( xTaskHandle pxTask )
	{
		unsigned portBASE_TYPE uxReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		uxReturn = uxTaskPriorityGet( pxTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return uxReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskPrioritySet == 1 )
	void MPU_vTaskPrioritySet( xTaskHandle pxTask, unsigned portBASE_TYPE uxNewPriority )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskPrioritySet( pxTask, uxNewPriority );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskSuspend == 1 )
	void MPU_vTaskSuspend( xTaskHandle pxTaskToSuspend )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskSuspend( pxTaskToSuspend );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskSuspend == 1 )
	signed portBASE_TYPE MPU_xTaskIsTaskSuspended( xTaskHandle xTask )
	{
		signed portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskIsTaskSuspended( xTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskSuspend == 1 )
	void MPU_vTaskResume( xTaskHandle pxTaskToResume )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskResume( pxTaskToResume );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

void MPU_vTaskSuspendAll( void )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	vTaskSuspendAll();
    portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

signed portBASE_TYPE MPU_xTaskResumeAll( void )
{
	signed portBASE_TYPE xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskResumeAll();
    portRESET_PRIVILEGE( xRunningPrivileged );
    return xReturn;
}


/*----------------------------------------------------------------------------*/

portTickType MPU_xTaskGetTickCount( void )
{
	portTickType xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskGetTickCount();
    portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

unsigned portBASE_TYPE MPU_uxTaskGetNumberOfTasks( void )
{
	unsigned portBASE_TYPE uxReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	uxReturn = uxTaskGetNumberOfTasks();
    portRESET_PRIVILEGE( xRunningPrivileged );
	return uxReturn;
}


/*----------------------------------------------------------------------------*/

#if ( configUSE_TRACE_FACILITY == 1 )
	void MPU_vTaskList( signed char *pcWriteBuffer )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskList( pcWriteBuffer );
		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configGENERATE_RUN_TIME_STATS == 1 )
	void MPU_vTaskGetRunTimeStats( signed char *pcWriteBuffer )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskGetRunTimeStats( pcWriteBuffer );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	void MPU_vTaskSetApplicationTaskTag( xTaskHandle xTask, pdTASK_HOOK_CODE pxTagValue )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		vTaskSetApplicationTaskTag( xTask, pxTagValue );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	pdTASK_HOOK_CODE MPU_xTaskGetApplicationTaskTag( xTaskHandle xTask )
	{
		pdTASK_HOOK_CODE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetApplicationTaskTag( xTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	portBASE_TYPE MPU_xTaskCallApplicationTaskHook( xTaskHandle xTask, void *pvParameter )
	{
		portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
	unsigned portBASE_TYPE MPU_uxTaskGetStackHighWaterMark( xTaskHandle xTask )
	{
		unsigned portBASE_TYPE uxReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		uxReturn = uxTaskGetStackHighWaterMark( xTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return uxReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_xTaskGetCurrentTaskHandle == 1 )
	xTaskHandle MPU_xTaskGetCurrentTaskHandle( void )
	{
		xTaskHandle xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetCurrentTaskHandle();
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_xTaskGetSchedulerState == 1 )
	portBASE_TYPE MPU_xTaskGetSchedulerState( void )
	{
		portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetSchedulerState();
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

xQueueHandle MPU_xQueueGenericCreate( unsigned portBASE_TYPE uxQueueLength, unsigned portBASE_TYPE uxItemSize, unsigned char ucQueueType )
{
	xQueueHandle xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

signed portBASE_TYPE MPU_xQueueGenericSend( xQueueHandle xQueue, const void * const pvItemToQueue, portTickType xTicksToWait, portBASE_TYPE xCopyPosition )
{
	signed portBASE_TYPE xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

unsigned portBASE_TYPE MPU_uxQueueMessagesWaiting( const xQueueHandle pxQueue )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	unsigned portBASE_TYPE uxReturn;
	uxReturn = uxQueueMessagesWaiting( pxQueue );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return uxReturn;
}


/*----------------------------------------------------------------------------*/

signed portBASE_TYPE MPU_xQueueGenericReceive( xQueueHandle pxQueue, void * const pvBuffer, portTickType xTicksToWait, portBASE_TYPE xJustPeeking )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
	signed portBASE_TYPE xReturn;
	xReturn = xQueueGenericReceive( pxQueue, pvBuffer, xTicksToWait, xJustPeeking );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

#if ( configUSE_MUTEXES == 1 )
	xQueueHandle MPU_xQueueCreateMutex( void )
	{
		xQueueHandle xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();
		xReturn = xQueueCreateMutex( queueQUEUE_TYPE_MUTEX );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configUSE_COUNTING_SEMAPHORES == 1
	xQueueHandle MPU_xQueueCreateCountingSemaphore( unsigned portBASE_TYPE uxCountValue, unsigned portBASE_TYPE uxInitialCount )
	{
		xQueueHandle xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueCreateCountingSemaphore( uxCountValue, uxInitialCount );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_MUTEXES == 1 )
	portBASE_TYPE MPU_xQueueTakeMutexRecursive( xQueueHandle xMutex, portTickType xBlockTime )
	{
		portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_MUTEXES == 1 )
	portBASE_TYPE MPU_xQueueGiveMutexRecursive( xQueueHandle xMutex )
	{
		portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueGiveMutexRecursive( xMutex );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configUSE_ALTERNATIVE_API == 1
	signed portBASE_TYPE MPU_xQueueAltGenericSend( xQueueHandle pxQueue, const void * const pvItemToQueue, portTickType xTicksToWait, portBASE_TYPE xCopyPosition )
	{
		signed portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		xReturn = 	signed portBASE_TYPE xQueueAltGenericSend( pxQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configUSE_ALTERNATIVE_API == 1
	signed portBASE_TYPE MPU_xQueueAltGenericReceive( xQueueHandle pxQueue, void * const pvBuffer, portTickType xTicksToWait, portBASE_TYPE xJustPeeking )
	{
		signed portBASE_TYPE xReturn;
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueAltGenericReceive( pxQueue, pvBuffer, xTicksToWait, xJustPeeking );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configQUEUE_REGISTRY_SIZE > 0
	void MPU_vQueueAddToRegistry( xQueueHandle xQueue, signed char *pcName )
	{
		portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

		vQueueAddToRegistry( xQueue, pcName );

		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

void *MPU_pvPortMalloc( size_t xSize )
{
	void *pvReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	pvReturn = pvPortMalloc( xSize );

	portRESET_PRIVILEGE( xRunningPrivileged );

	return pvReturn;
}


/*----------------------------------------------------------------------------*/

void MPU_vPortFree( void *pv )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	vPortFree( pv );

	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

void MPU_vPortInitialiseBlocks( void )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	vPortInitialiseBlocks();

	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

size_t MPU_xPortGetFreeHeapSize( void )
{
	size_t xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	xReturn = xPortGetFreeHeapSize();

	portRESET_PRIVILEGE( xRunningPrivileged );

	return xReturn;
}


/*----------------------------------------------------------------------------*/

void MPU_vQueueDelete( xQueueHandle xQueue )
{
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	vQueueDelete( xQueue );

	portRESET_PRIVILEGE( xRunningPrivileged );
}

/*----------------------------------------------------------------------------*/
#if configUSE_TIMERS == 1

xTimerHandle MPU_xTimerCreate( const signed char * pcTimerName, portTickType xTimerPeriodInTicks, unsigned portBASE_TYPE uxAutoReload, void *pvTimerID, tmrTIMER_CALLBACK pxCallbackFunction )
{
	xTimerHandle xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	xReturn = xTimerCreate( pcTimerName, xTimerPeriodInTicks, uxAutoReload, pvTimerID, pxCallbackFunction );

	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

void * MPU_pvTimerGetTimerID( xTimerHandle xTimer )
{
	void *xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	xReturn = (void *) pvTimerGetTimerID( xTimer );

	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

portBASE_TYPE MPU_xTimerIsTimerActive( xTimerHandle xTimer )
{
	portBASE_TYPE xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	xReturn = xTimerIsTimerActive( xTimer );

	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

portBASE_TYPE MPU_xTimerGenericCommand( xTimerHandle xTimer, portBASE_TYPE xCommandID, portTickType xOptionalValue, signed portBASE_TYPE *pxHigherPriorityTaskWoken, portTickType xBlockTime )
{
	portBASE_TYPE xReturn;
	portBASE_TYPE xRunningPrivileged = prvRaisePrivilege();

	xReturn = xTimerGenericCommand( xTimer, xCommandID, xOptionalValue, pxHigherPriorityTaskWoken, xBlockTime );

	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

#endif
