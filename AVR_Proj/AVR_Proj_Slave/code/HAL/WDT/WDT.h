#ifndef WDT_H
#define WDT_H

#include "Types.h"
#include <avr/wdt.h>

#define WDT_Reset wdt_reset

extern void WDT_Init(uint8 wdt_prescalar);
extern void WDT_Disable(void);
extern void WDT_Enable(void);
extern Func_ReturnType WDT_SetPrescalar(uint8 wdt_prescalar);

#endif