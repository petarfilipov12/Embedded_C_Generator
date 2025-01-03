#include "GPT_Service.h"
#include "GEN_GPT_Service_DATA_CFG.h"
#include "GEN_GPT_Service_SERVER_PORTS_CFG.h"
#include "GEN_GPT_Service_CLIENT_PORTS_CFG.h"
#include "GPT.h"

void GPT_Service_Init(void)
{
#if GPT_Service_GPT_Service_GPTs_Count > 0
    uint8 timer_id = 0;

    GPT_Service_GptCfg_data_INIT_FUNC();

    for(timer_id = 0; timer_id < GPT_Service_GPT_Service_GPTs_Count; timer_id++)
    {
        GPT_Service_GptCfg_data[timer_id].status = GPT_Init_Timer(
            timer_id,
            GPT_Service_GptCfg_data[timer_id].gptMode,
            GPT_Service_GptCfg_data[timer_id].compareValue,
            GPT_Service_GptCfg_data[timer_id].prescaler
        );
    }
#endif
}

Func_ReturnType GPT_Service_Set_Compare_Value(uint8 timer_id, uint8 compare_val)
{
    Func_ReturnType ret = RET_NOT_OK;

#if GPT_Service_GPT_Service_GPTs_Count > 0
    ret = GPT_Service_GptCfg_data[timer_id].status;

    if(RET_OK == ret)
    {
        ret = GPT_Timer_Set_Compare_Value(timer_id, compare_val);
        if(RET_OK == ret)
        {
            GPT_Service_GptCfg_data[timer_id].compareValue = compare_val;
        }
    }
#endif
    return ret;
}