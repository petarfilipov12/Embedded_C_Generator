#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

#include "Types.h"
#include "GPT_Service.h"
#include "GEN_PWM_Service_CFG.h"

extern Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle);

#endif