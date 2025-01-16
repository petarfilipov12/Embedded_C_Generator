#include "GEN_WDT_Service_DATA_CFG.h"

WDT_Service_WdtCfg_t WDT_Service_WdtCfg_data[WDT_Service_WDT_Service_WDTs_Count];

inline void WDT_Service_WdtCfg_data_INIT_FUNC(void)
{
	WDT_Service_WdtCfg_data[0].id = WDT_Service_WDT_0_Id;
	WDT_Service_WdtCfg_data[0].prescaler = WDT_Service_WDT_0_Prescaler;
	WDT_Service_WdtCfg_data[0].status = RET_NOT_OK;
}