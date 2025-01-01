#include "GEN_PWM_Service_DATA_CFG.h"

PWM_Service_PwmCfg_t PWM_Service_PwmCfg_data[PWM_Service_PWM_Service_Pins_Count];

inline void PWM_Service_PwmCfg_data_INIT_FUNC(void)
{
	PWM_Service_PwmCfg_data[0].gptTimerRef = PWM_Service_PWM_PIN_0_GptTimerRef;
	PWM_Service_PwmCfg_data[0].id = PWM_Service_PWM_PIN_0_Id;
	PWM_Service_PwmCfg_data[0].status = RET_NOT_OK;
}