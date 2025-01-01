#ifndef GEN_DATA_CFG_ADC_SERVICE_H
#define GEN_DATA_CFG_ADC_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "ADC_Service.h"
#include "GEN_ADC_Service_CFG.h"

extern ADC_Service_AdcCfg_t ADC_Service_AdcHwCfg_data[ADC_Service_ADC_COUNT];

extern inline void ADC_Service_AdcHwCfg_data_INIT_FUNC(void);

#endif