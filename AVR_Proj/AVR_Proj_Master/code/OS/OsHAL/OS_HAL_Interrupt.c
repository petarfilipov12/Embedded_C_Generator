#include "OS_HAL_Interrupt.h"
#include <avr/interrupt.h>

inline void OS_HAL_Interrupt_DisableGlobal(void)
{
    cli();
}

inline void OS_HAL_Interrupt_EnableGlobal(void)
{
    sei();
}