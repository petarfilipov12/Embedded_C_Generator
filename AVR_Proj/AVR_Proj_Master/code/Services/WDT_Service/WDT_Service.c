#include "WDT_Service.h"

boolean gbWdtEnabled = FALSE;

void WDT_Service_Init(void)
{
    WDT_Init(WDT_TIMEOUT_PRESCALAR_INIT);
    gbWdtEnabled = FALSE;

    WDT_Service_WDT_Enable();
}

void WDT_Service_WDT_Disable(void)
{
    //Disable Interrupts
    WDT_Disable();
    //Enable interrupts

    gbWdtEnabled = FALSE;
}

void WDT_Service_WDT_Enable(void)
{
    //Disable Interrupts
    WDT_Enable();
    //Enable interrupts

    gbWdtEnabled = TRUE;
}

Func_ReturnType WDT_Service_WDT_SetPrescalar(uint8 wdt_prescalar)
{
    return WDT_SetPrescalar(wdt_prescalar);
}

void WDT_Service_Cyclic(void)
{
    if(gbWdtEnabled)
    {
        WDT_Reset();
    }
    
}