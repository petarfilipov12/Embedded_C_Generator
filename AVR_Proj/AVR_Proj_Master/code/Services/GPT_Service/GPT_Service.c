#include "GPT_Service.h"
#include "GPT.h"

#if GPT_Service_GPT_Service_GPTs_Count > 0
typedef struct{
    uint8 compare_val;
    uint8 timer_mode;
    uint8 freq_prescalar;
    Func_ReturnType status;
}GPT_Service_TimerCfg_t;

GPT_Service_TimerCfg_t GPT_Service_Timer_data[GPT_Service_GPT_Service_GPTs_Count] = {GPT_Service_Data_Init};
#endif

void GPT_Service_Init(void)
{
#if GPT_Service_GPT_Service_GPTs_Count > 0
    uint8 timer_id = 0;

    for(timer_id = 0; timer_id < GPT_Service_GPT_Service_GPTs_Count; timer_id++)
    {
        GPT_Service_Timer_data[timer_id].status = GPT_Init_Timer(
            timer_id,
            GPT_Service_Timer_data[timer_id].timer_mode,
            GPT_Service_Timer_data[timer_id].compare_val,
            GPT_Service_Timer_data[timer_id].freq_prescalar
        );
    }
#endif
}

Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val)
{
    Func_ReturnType ret = RET_NOT_OK;

#if GPT_Service_TIMER_COUNT > 0
    ret = GPT_Service_Timer_data[timer_id].status;

    if(RET_OK == ret)
    {
        ret = GPT_Timer_Set_Compare_Value(timer_id, compare_val);
        if(RET_OK == ret)
        {
            GPT_Service_Timer_data[timer_id].compare_val = compare_val;
        }
    }
#endif
    return ret;
}