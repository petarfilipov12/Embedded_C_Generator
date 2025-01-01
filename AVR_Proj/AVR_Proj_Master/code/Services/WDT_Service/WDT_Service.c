#include "WDT_Service.h"
#include "GEN_WDT_Service_DATA_CFG.h"
#include "GEN_WDT_Service_SERVER_PORTS_CFG.h"
#include "GEN_WDT_Service_CLIENT_PORTS_CFG.h"
#include "WDT.h"

void WDT_Service_Init(void)
{
    #if WDT_Service_WDT_Service_WDTs_Count > 0
    uint8 wdt_id = 0;

    WDT_Service_WdtCfg_data_INIT_FUNC();

    for(wdt_id = 0; wdt_id < WDT_Service_WDT_Service_WDTs_Count; wdt_id++)
    {
        WDT_Init(wdt_id, WDT_Service_WdtCfg_data[wdt_id].prescaler);

        if(WDT_Service_WdtCfg_data[wdt_id].bIsEnabled)
        {
            WDT_Service_WDT_Enable(wdt_id);
        }
    }
    #endif
}

Func_ReturnType WDT_Service_WDT_Disable(uint8 wdt_id)
{
    Func_ReturnType ret = RET_NOT_OK;

#if WDT_Service_WDT_Service_WDTs_Count > 0
    //Disable Interrupts
    ret = WDT_Disable(wdt_id);
    //Enable interrupts

    WDT_Service_WdtCfg_data[wdt_id].bIsEnabled = FALSE;
#endif

    return ret;
}

Func_ReturnType WDT_Service_WDT_Enable(uint8 wdt_id)
{
    Func_ReturnType ret = RET_NOT_OK;

#if WDT_Service_WDT_Service_WDTs_Count > 0
    //Disable Interrupts
    ret = WDT_Enable(wdt_id);
    //Enable interrupts

    WDT_Service_WdtCfg_data[wdt_id].bIsEnabled = TRUE;
#endif

    return ret;
}

Func_ReturnType WDT_Service_WDT_SetPrescalar(uint8 wdt_id, uint32 wdt_prescalar)
{
    Func_ReturnType ret = RET_NOT_OK;

#if WDT_Service_WDT_Service_WDTs_Count > 0
    ret = WDT_SetPrescalar(wdt_id, wdt_prescalar);
#endif

    return ret;
}

void WDT_Service_Cyclic(void)
{
#if WDT_Service_WDT_Service_WDTs_Count > 0
    uint8 wdt_id = 0;

    for(wdt_id = 0; wdt_id < WDT_Service_WDT_Service_WDTs_Count; wdt_id++)
    if(WDT_Service_WdtCfg_data[wdt_id].bIsEnabled)
    {
        WDT_Reset(wdt_id);
    }
#endif
}