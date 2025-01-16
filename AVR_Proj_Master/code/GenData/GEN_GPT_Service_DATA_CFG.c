#include "GEN_GPT_Service_DATA_CFG.h"

GPT_Service_GptCfg_t GPT_Service_GptCfg_data[GPT_Service_GPT_Service_GPTs_Count];

inline void GPT_Service_GptCfg_data_INIT_FUNC(void)
{
	GPT_Service_GptCfg_data[0].compareValue = GPT_Service_GPT_TIMER_0_CompareValue;
	GPT_Service_GptCfg_data[0].gptMode = GPT_Service_GPT_TIMER_0_GptMode;
	GPT_Service_GptCfg_data[0].id = GPT_Service_GPT_TIMER_0_Id;
	GPT_Service_GptCfg_data[0].prescaler = GPT_Service_GPT_TIMER_0_Prescaler;
	GPT_Service_GptCfg_data[0].status = RET_NOT_OK;
}