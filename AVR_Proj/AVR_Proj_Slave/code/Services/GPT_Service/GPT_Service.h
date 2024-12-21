#ifndef GPT_SERVICE_H
#define GPT_SERVICE_H

#define GPT_Service_TIMER_MODE_NORMAL   0
#define GPT_Service_TIMER_MODE_PWM      1

#include "GPT.h"

/*  Start Timer_data  */
#define GPT_Service_TIMER_0_ID              0
#define GPT_Service_TIMER_0_MODE            GPT_Service_TIMER_MODE_PWM
#define GPT_Service_TIMER_0_COMPARE_VALUE   0
#define GPT_Service_TIMER_0_FREQ_PRESCALER  64

#define GPT_Service_TIMER_COUNT             1
/*  End Timer_data  */

extern Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val);

#endif