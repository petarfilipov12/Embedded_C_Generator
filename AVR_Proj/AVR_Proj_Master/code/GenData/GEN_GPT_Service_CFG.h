#ifndef GEN_GPT_SERVICE_CFG_H
#define GEN_GPT_SERVICE_CFG_H

#include "Types.h"

#define GPT_Service_GPT_Service_GPTs_Count 1

#define GPT_Service_GPT_TIMER_0_CompareValue 0
#define GPT_Service_GPT_TIMER_0_GptMode GPT_MODE_PWM
#define GPT_Service_GPT_TIMER_0_Id 0
#define GPT_Service_GPT_TIMER_0_Prescaler 64


#define GPT_Service_Data_Init \
/* GPT_TIMER_0 */{GPT_Service_GPT_TIMER_0_CompareValue, GPT_Service_GPT_TIMER_0_GptMode, GPT_Service_GPT_TIMER_0_Id, GPT_Service_GPT_TIMER_0_Prescaler, RET_NOT_OK}

#endif