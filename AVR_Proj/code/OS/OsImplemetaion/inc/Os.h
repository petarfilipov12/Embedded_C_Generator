#ifndef OS_H
#define OS_H

#include "Types.h"
#include "OsHAL.h"
#include "LedIndicator.h"

#define OS_TASK OsHAL_TASK
#define OS_CreateTask OsHAL_CreateTask
#define OS_Run Os_HAL_Run

#define OS_GetTaskInitRunnables(TaskName) TaskName##_InitRunnables
#define OS_GetTaskCyclicRunnables(TaskName) TaskName##_CyclicRunnables

#define Task_100ms_InitRunnables    \
CompLedIndicator_init();

#define Task_100ms_CyclicRunnables   \
CompLedIndicator_cyclic_100ms();

#endif