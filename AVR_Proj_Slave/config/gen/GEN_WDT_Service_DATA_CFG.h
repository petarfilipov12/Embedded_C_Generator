#ifndef GEN_WDT_SERVICE_DATA_CFG_H
#define GEN_WDT_SERVICE_DATA_CFG_H

#include "Types.h"
#include "Queue.h"
#include "GEN_WDT_Service_CFG.h"
#include "WDT_Service.h"

extern WDT_Service_WdtCfg_t WDT_Service_WdtCfg_data[WDT_Service_WDT_Service_WDTs_Count];

extern inline void WDT_Service_WdtCfg_data_INIT_FUNC(void);

#endif