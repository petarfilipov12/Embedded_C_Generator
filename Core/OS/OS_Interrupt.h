#ifndef OS_INTERRUPT_H
#define OS_INTERRUPT_H

#include "Types.h"
#include "OS_HAL_Interrupt.h"

extern inline void OS_Interrupt_DisableGlobal(void);
extern inline void OS_Interrupt_EnableGlobal(void);

#endif