#ifndef OS_H
#define OS_H

#include "Types.h"
#include "OsHAL.h"

#define OS_ADD_QUOTE(s) #s 

#define OS_TASK OsHAL_TASK
#define OS_CreateTask(taskName, cycle, stackSize, priority) OsHAL_CreateTask(taskName, OS_ADD_QUOTE(taskName), cycle, stackSize, priority)
#define OS_Run Os_HAL_Run

#include "GEN_OS_CFG.h"
#include "OS_HAL_Interrupt.h"

#endif