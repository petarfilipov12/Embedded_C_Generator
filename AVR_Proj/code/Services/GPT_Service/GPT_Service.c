#include "GPT_Service.h"

typedef struct{
    uint8 timer_mode;
    uint8 compare_val;
    uint8 freq_prescalar;
    Func_ReturnType status;
}GPT_Service_TimerCfg_t;

GPT_Service_TimerCfg_t GPT_Service_Timer_data[GPT_Service_TIMER_COUNT] = {
    {GPT_Service_TIMER_0_MODE, GPT_Service_TIMER_0_COMPARE_VALUE, GPT_Service_TIMER_0_FREQ_PRESCALER, RET_NOT_OK}, //TIMER_0
};

void GPT_Service_Init(void)
{
    uint8 timer_id = 0;

    for(timer_id=0; timer_id<GPT_Service_TIMER_COUNT; timer_id++)
    {
        GPT_Service_Timer_data[timer_id].status = GPT_Init_Timer(
            timer_id,
            GPT_Service_Timer_data[timer_id].timer_mode,
            GPT_Service_Timer_data[timer_id].compare_val,
            GPT_Service_Timer_data[timer_id].freq_prescalar
        );
    }
}

Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val)
{
    Func_ReturnType ret = GPT_Service_Timer_data[timer_id].status;

    if(RET_OK == ret)
    {
        ret = GPT_Timer_Set_Compare_Value(timer_id, compare_val);
        if(RET_OK == ret)
        {
            GPT_Service_Timer_data[timer_id].compare_val = compare_val;
        }
    }

    return ret;
}