#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

#include "Types.h"
#include "GPT_Service.h"
#include "GEN_PWM_Service_CFG.h"

typedef struct{
    uint8 gptTimerRef;
    uint8 id;
    Func_ReturnType status;
}PWM_Service_PwmCfg_t;

#endif