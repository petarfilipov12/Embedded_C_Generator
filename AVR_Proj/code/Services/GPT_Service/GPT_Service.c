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
    uint8 i = 0;

    for(i=0; i<GPT_Service_TIMER_COUNT; i++)
    {
        GPT_Service_Timer_data[i].status = GPT_Init_Timer(
            i,
            GPT_Service_Timer_data[i].timer_mode,
            GPT_Service_Timer_data[i].compare_val,
            GPT_Service_Timer_data[i].freq_prescalar
        );
    }
}

Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val)
{
    Func_ReturnType ret = RET_NOT_OK;

    ret = GPT_Timer_Set_Compare_Value(timer_id, compare_val);

    return ret;
}