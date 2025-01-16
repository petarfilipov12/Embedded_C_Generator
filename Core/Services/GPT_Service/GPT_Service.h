#ifndef GPT_SERVICE_H
#define GPT_SERVICE_H

#define GPT_Service_TIMER_MODE_NORMAL   0
#define GPT_Service_TIMER_MODE_PWM      1

#include "Types.h"
#include "GEN_GPT_Service_CFG.h"

typedef struct{
    uint8 compareValue;
    uint8 gptMode;
    uint8 id;
    uint8 prescaler;
    Func_ReturnType status;
}GPT_Service_GptCfg_t;

#endif