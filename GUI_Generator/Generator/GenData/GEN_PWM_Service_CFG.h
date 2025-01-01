#ifndef GEN_PWM_SERVICE_CFG_H
#define GEN_PWM_SERVICE_CFG_H

#include "Types.h"

#define PWM_Service_PWM_Service_Pins_Count 1

#define PWM_Service_PWM_PIN_0_GptTimerRef GPT_TIMER_0
#define PWM_Service_PWM_PIN_0_Id 0


#define PWM_Service_Data_Init \
/* PWM_PIN_0 */{PWM_Service_PWM_PIN_0_GptTimerRef, PWM_Service_PWM_PIN_0_Id, RET_NOT_OK}

#endif