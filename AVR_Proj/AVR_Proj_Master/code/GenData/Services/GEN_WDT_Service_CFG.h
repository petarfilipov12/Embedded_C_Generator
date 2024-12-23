#ifndef GEN_CFG_WDT_SERVICE_H
#define GEN_CFG_WDT_SERVICE_H

#define WDT_Service_WDT_0_ID                0
#define WDT_Service_WDT_0_PRESCALAR_INIT    512000u
#define WDT_Service_WDT_0_ENABLED_INIT      TRUE

#define WDT_Service_WDT_COUNT               1

#define WDT_Service_Wdt_data_INIT \
/*WDT_0*/{WDT_Service_WDT_0_PRESCALAR_INIT, RET_NOT_OK, WDT_Service_WDT_0_ENABLED_INIT},
#endif