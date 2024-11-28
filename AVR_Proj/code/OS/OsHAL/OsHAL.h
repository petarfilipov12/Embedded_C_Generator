#ifndef OS_HAL_H
#define OS_HAL_H

#include "FreeRTOS.h"
#include "task.h"

#include "Os.h"

#define Os_HAL_Run vTaskStartScheduler

typedef void (*Os_TaskType_t)(void*);

#define OsHAL_TASK(TaskName, Period_ms, StackSize, Priority, InitRunnables, CyclicRunnables)                    \
void TaskName(void *pvParms)                                                                                    \
{                                                                                                               \
	portTickType xLastWakeTime;                                                                                 \
    InitRunnables                                                                                               \
    xLastWakeTime = xTaskGetTickCount();                                                                        \
	for(;;)                                                                                                     \
    {                                                                                                           \
		CyclicRunnables                                                                                         \
		vTaskDelayUntil(&xLastWakeTime, (portTickType)(portTICK_PERIOD_MS * Period_ms) );                       \
	}                                                                                                           \
}

uint8_t OsHAL_CreateTask(Os_TaskType_t pTaskP, char* TaskName, uint8_t u8PeriodP, uint32_t u32StackSizeP, uint8_t u8PriorityP);

#endif

