#include "WDT.h"

uint8 gu8WdtPrescalarMask = 0;

Func_ReturnType WDT_Init(uint8 wdt_id, uint32 wdt_prescalar)
{
    return WDT_SetPrescalar(wdt_id, wdt_prescalar);
}

Func_ReturnType WDT_Disable(uint8 wdt_id)
{
    //Disable Interrupts

    wdt_reset();

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00u;

    //Enable interrupts

    return RET_OK;
}

Func_ReturnType WDT_Enable(uint8 wdt_id)
{
    //Disable Interrupts

    wdt_reset();

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR |= (1 << WDE) | gu8WdtPrescalarMask;

    //Enable interrupts

    return RET_OK;
}

Func_ReturnType WDT_SetPrescalar(uint8 wdt_id, uint32 wdt_prescalar)
{
    uint8 wdt_prescalar_hex = 0x00u;

    switch (wdt_prescalar)
    {
    case 2000u:
        wdt_prescalar_hex = 0x00u;
        break;
    case 4000u:
        wdt_prescalar_hex = 0x01u;
        break;
    case 8000u:
        wdt_prescalar_hex = 0x02u;
        break;
    case 16000u:
        wdt_prescalar_hex = 0x03u;
        break;
    case 32000u:
        wdt_prescalar_hex = 0x04u;
        break;
    case 64000u:
        wdt_prescalar_hex = 0x05u;
        break;
    case 128000u:
        wdt_prescalar_hex = 0x06u;
        break;
    case 256000u:
        wdt_prescalar_hex = 0x07u;
        break;
    case 512000u:
        wdt_prescalar_hex = 0x08u;
        break;
    case 1024000u:
        wdt_prescalar_hex = 0x09u;
        break;
    
    default:
        wdt_prescalar_hex = 0x00u;
        break;
    }


    if(wdt_prescalar_hex >= 0x08u)
    {
        gu8WdtPrescalarMask = 0x20 | (wdt_prescalar_hex - 0x08u);
    }
    else
    {
        gu8WdtPrescalarMask = wdt_prescalar_hex;
    }

    return RET_OK;
}

inline void WDT_Reset(uint8 wdt_id)
{
    wdt_reset();
}