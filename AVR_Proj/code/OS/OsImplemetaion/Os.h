#ifndef OS_H
#define OS_H

#include "Types.h"
#include "OsHAL.h"

#define OS_TASK OsHAL_TASK
#define OS_CreateTask OsHAL_CreateTask
#define OS_Run Os_HAL_Run

#define OS_GetTaskInitRunnables(TaskName) TaskName##_InitRunnables
#define OS_GetTaskCyclicRunnables(TaskName) TaskName##_CyclicRunnables

/* Start Task_200ms */
#define Task_200ms_InitRunnables    \
IO_Service_Init();  \
GPT_Service_Init(); \
PWM_Service_Init(); \
CompLedIndicator_Init();

#define Task_200ms_CyclicRunnables   \
CompLedIndicator_cyclic_100ms();    \
CompSensor_Cyclic_100ms();
/* End Task_200ms */

/* Start Task_10ms */
#define Task_10ms_InitRunnables    \
WDT_Service_Init(); \
UART_Service_Init();    \
ADC_Service_Init();

#define Task_10ms_CyclicRunnables   \
WDT_Service_Cyclic();   \
UART_Service_Cyclic();  \
ADC_Service_Cyclic();
/* End Task_10ms */

#endif