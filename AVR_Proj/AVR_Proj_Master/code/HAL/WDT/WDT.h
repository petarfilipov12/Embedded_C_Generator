#ifndef WDT_H
#define WDT_H

#include "Types.h"
#include <avr/wdt.h>

extern Func_ReturnType WDT_Init(uint8 wdt_id, uint32 wdt_prescalar);
extern Func_ReturnType WDT_Disable(uint8 wdt_id);
extern Func_ReturnType WDT_Enable(uint8 wdt_id);
extern Func_ReturnType WDT_SetPrescalar(uint8 wdt_id, uint32 wdt_prescalar);
extern inline void WDT_Reset(uint8 wdt_id);

#endif