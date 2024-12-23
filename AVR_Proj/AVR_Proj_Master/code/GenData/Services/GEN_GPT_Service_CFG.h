#ifndef GEN_CFG_GPT_SERVICE_H
#define GEN_CFG_GPT_SERVICE_H

#define GPT_Service_TIMER_0_ID              0
#define GPT_Service_TIMER_0_MODE            GPT_Service_TIMER_MODE_PWM
#define GPT_Service_TIMER_0_COMPARE_VALUE   0
#define GPT_Service_TIMER_0_FREQ_PRESCALER  64

#define GPT_Service_TIMER_COUNT             1

#define GPT_Service_Timer_data_INIT \
    {GPT_Service_TIMER_0_MODE, GPT_Service_TIMER_0_COMPARE_VALUE, GPT_Service_TIMER_0_FREQ_PRESCALER, RET_NOT_OK}, //TIMER_0

#endif