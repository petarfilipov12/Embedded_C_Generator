#include "WDT.h"
#include "WDT_Service_Prescalars.h"

uint8 gu8WdtPrescalarMask = 0;

void WDT_Init(uint8 wdt_prescalar)
{
    WDT_SetPrescalar(wdt_prescalar);
}

void WDT_Disable(void)
{
    //Disable Interrupts

    wdt_reset();

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00u;

    //Enable interrupts
}

void WDT_Enable(void)
{
    //Disable Interrupts

    wdt_reset();

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR |= (1 << WDE) | gu8WdtPrescalarMask;

    //Enable interrupts
}

Func_ReturnType WDT_SetPrescalar(uint8 wdt_prescalar)
{
    if(wdt_prescalar >= eWdtTimeout_4s)
    {
        gu8WdtPrescalarMask = 0x20 | (wdt_prescalar - eWdtTimeout_4s);
    }
    else
    {
        gu8WdtPrescalarMask = wdt_prescalar;
    }

    return RET_OK;
}