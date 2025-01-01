#ifndef GEN_WDT_SERVICE_CFG_H
#define GEN_WDT_SERVICE_CFG_H

#include "Types.h"

#define WDT_Service_WDT_Service_WDTs_Count 1

#define WDT_Service_WDT_0_Id 0
#define WDT_Service_WDT_0_Prescaler 512000


#define WDT_Service_Data_Init \
/* WDT_0 */{WDT_Service_WDT_0_Id, WDT_Service_WDT_0_Prescaler, RET_NOT_OK}

#endif