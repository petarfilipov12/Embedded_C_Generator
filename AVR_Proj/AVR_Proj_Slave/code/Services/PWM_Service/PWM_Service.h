#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

#include "PWM.h"

/*  Start Pin_data  */
#define PWM_Service_PIN_0_ID             0

#define PWM_Service_PIN_COUNT            1
/*  End Pin_data  */

extern Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle);

#endif