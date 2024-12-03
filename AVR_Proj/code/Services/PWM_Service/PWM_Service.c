#include "PWM_Service.h"
#include "GPT_Service.h"

typedef struct{
    uint8 timer_id;
    Func_ReturnType status;
}PWM_Service_PinCfg_t;

PWM_Service_PinCfg_t PWM_Service_Pin_data[PWM_Service_PIN_COUNT] = {
    {GPT_Service_TIMER_0_ID, RET_NOT_OK}, //Pin_0
};

void PWM_Service_Init(void)
{
    uint8 pin_id = 0;

    for(pin_id=0; pin_id<PWM_Service_PIN_COUNT; pin_id++)
    {
        PWM_Service_Pin_data[pin_id].status = PWM_Init_Pin(pin_id);
    }
}

Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle)
{
    Func_ReturnType ret = PWM_Service_Pin_data[pin_id].status;

    if(RET_OK == ret)
    {
        ret = GPT_Service_Set_Compare_Value(PWM_Service_Pin_data[pin_id].timer_id, duty_cycle);
    }
    
    return ret;
}