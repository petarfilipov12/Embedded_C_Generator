#ifndef WDT_SERVICE_H
#define WDT_SERVICE_H

#include "Types.h"
#include "GEN_WDT_Service_CFG.h"

typedef struct{
    uint32 prescaler;
    uint8 id;
    Func_ReturnType status;
    boolean bIsEnabled
}WDT_Service_WdtCfg_t;

#endif