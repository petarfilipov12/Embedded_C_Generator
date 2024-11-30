#include "PWM_Service.h"

typedef struct{
    uint8 freq_prescalar;
    Func_ReturnType status;
}PWM_Service_TimerCfg_t;

PWM_Service_TimerCfg_t PWM_Service_Timer_data[PWM_Service_TIMER_COUNT] = {
    {PWM_Service_TIMER_0_FREQ_PRESCALER, RET_NOT_OK}, //TIMER_0
};

typedef struct{
    uint8 timer_id;
    Func_ReturnType status;
}PWM_Service_PinCfg_t;

PWM_Service_PinCfg_t PWM_Service_Pin_data[PWM_Service_PIN_COUNT] = {
    {PWM_Service_TIMER_0_ID, RET_NOT_OK}, //Pin_0
};

void PWM_Service_Init(void)
{
    uint8 i = 0;

    for(i=0; i<PWM_Service_TIMER_COUNT; i++)
    {
        PWM_Service_Timer_data[i].status = PWM_Init_Timer(i, PWM_Service_Timer_data[i].freq_prescalar);
    }

    for(i=0; i<PWM_Service_PIN_COUNT; i++)
    {
        PWM_Service_Pin_data[i].status = PWM_Init_Pin(i);
    }
}

Func_ReturnType PWM_Service_Set_Pin(uint8 pin_id, uint8 duty_cycle)
{
    Func_ReturnType ret = RET_NOT_OK;

    if( (RET_OK == PWM_Service_Timer_data[PWM_Service_Pin_data[pin_id].timer_id].status ) && (RET_OK == PWM_Service_Pin_data[pin_id].status) )
    {
        ret = PWM_Set_Pin(pin_id, duty_cycle);
    }
    
    return ret;
}