#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

#include "PWM.h"

/*  Start Timer_data  */
#define PWM_Service_TIMER_0_ID              0
#define PWM_Service_TIMER_0_FREQ_PRESCALER  64

#define PWM_Service_TIMER_COUNT             1
/*  End Timer_data  */

/*  Start Pin_data  */
#define PWM_Service_PIN_0_ID             0

#define PWM_Service_PIN_COUNT            1
/*  End Pin_data  */

extern Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle);

#endif