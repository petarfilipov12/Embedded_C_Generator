#ifndef GEN_GPT_SERVICE_DATA_CFG_H
#define GEN_GPT_SERVICE_DATA_CFG_H

#include "Types.h"
#include "Queue.h"
#include "GEN_GPT_Service_CFG.h"
#include "GPT_Service.h"

extern GPT_Service_GptCfg_t GPT_Service_GptCfg_data[GPT_Service_GPT_Service_GPTs_Count];

extern inline void GPT_Service_GptCfg_data_INIT_FUNC(void);

#endif