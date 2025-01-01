#ifndef GEN_WDT_SERVICE_SERVER_PORTS_CFG_H
#define GEN_WDT_SERVICE_SERVER_PORTS_CFG_H

extern Func_ReturnType WDT_Service_Disable(uint8 wdt_id);
extern Func_ReturnType WDT_Service_Enable(uint8 wdt_id);
extern Func_ReturnType WDT_Service_SetPrescalar(uint8 wdt_id, uint32 wdt_prescalar);

#endif