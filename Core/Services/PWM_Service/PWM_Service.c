#include "PWM_Service.h"
#include "GEN_PWM_Service_DATA_CFG.h"
#include "GEN_PWM_Service_SERVER_PORTS_CFG.h"
#include "GEN_PWM_Service_CLIENT_PORTS_CFG.h"
#include "PWM.h"

void PWM_Service_Init(void)
{
#if PWM_Service_PWM_Service_Pins_Count > 0
    uint8 pin_id = 0;

    PWM_Service_PwmCfg_data_INIT_FUNC();

    for(pin_id = 0; pin_id < PWM_Service_PWM_Service_Pins_Count; pin_id++)
    {
        PWM_Service_PwmCfg_data[pin_id].status = PWM_Init_Pin(pin_id);
    }
#endif
}

Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle)
{
    Func_ReturnType ret = RET_NOT_OK;

#if PWM_Service_PWM_Service_Pins_Count > 0
    ret = PWM_Service_PwmCfg_data[pin_id].status;

    if(RET_OK == ret)
    {
        ret = GPT_Service_Set_Compare_Value(PWM_Service_PwmCfg_data[pin_id].gptTimerRef, duty_cycle);
    }
#endif
    
    return ret;
}