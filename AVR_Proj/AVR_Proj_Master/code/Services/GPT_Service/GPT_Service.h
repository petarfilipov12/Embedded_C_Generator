#ifndef GPT_SERVICE_H
#define GPT_SERVICE_H

#define GPT_Service_TIMER_MODE_NORMAL   0
#define GPT_Service_TIMER_MODE_PWM      1

#include "Types.h"
#include "GEN_GPT_Service_CFG.h"

extern Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val);

#endif