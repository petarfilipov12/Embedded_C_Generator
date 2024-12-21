#ifndef WDT_SERVICE_H
#define WDT_SERVICE_H

#include "WDT.h"
#include "WDT_Service_Prescalars.h"

#define WDT_TIMEOUT_PRESCALAR_INIT eWdtTimeout_32ms

extern void WDT_Service_WDT_Disable(void);
extern void WDT_Service_WDT_Enable(void);
extern Func_ReturnType WDT_Service_WDT_SetPrescalar(uint8 wdt_prescalar);

#endif