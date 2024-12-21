#include "OS_Interrupt.h"

boolean gbGlobalInteruptsEnebled = FALSE;

void OS_Interrupt_DisableGlobal(void)
{
    if(gbGlobalInteruptsEnebled)
    {
        OS_HAL_Interrupt_DisableGlobal();
        gbGlobalInteruptsEnebled = FALSE;
    }
}

void OS_Interrupt_EnableGlobal(void)
{
    if(!gbGlobalInteruptsEnebled)
    {
        OS_HAL_Interrupt_EnableGlobal();
        gbGlobalInteruptsEnebled = TRUE;
    }
}