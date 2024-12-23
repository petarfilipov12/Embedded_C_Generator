#ifndef WDT_SERVICE_H
#define WDT_SERVICE_H

#include "Types.h"
#include "GEN_WDT_Service_CFG.h"

#define WDT_Service_WDT_0_ID              0
#define WDT_Service_WDT_0_PRESCALAR_INIT            2000u
#define WDT_Service_WDT_0_ENABLED_INIT   FALSE

#define WDT_Service_WDT_COUNT             1

extern Func_ReturnType WDT_Service_WDT_Disable(uint8 wdt_id);
extern Func_ReturnType WDT_Service_WDT_Enable(uint8 wdt_id);
extern Func_ReturnType WDT_Service_WDT_SetPrescalar(uint8 wdt_id, uint32 wdt_prescalar);

#endif