#ifndef GEN_PWM_SERVICE_DATA_CFG_H
#define GEN_PWM_SERVICE_DATA_CFG_H

#include "Types.h"
#include "Queue.h"
#include "GEN_PWM_Service_CFG.h"
#include "PWM_Service.h"

extern PWM_Service_PwmCfg_t PWM_Service_PwmCfg_data[PWM_Service_PWM_Service_Pins_Count];

extern inline void PWM_Service_PwmCfg_data_INIT_FUNC(void);

#endif