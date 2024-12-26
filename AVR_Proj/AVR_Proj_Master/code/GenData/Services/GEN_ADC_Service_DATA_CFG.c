#include "GEN_ADC_Service_DATA_CFG.h"

uint8 ADC_Service_ADC_0_Buffer[ADC_Service_ADC_0_BUFFER_SIZE];

ADC_Service_AdcCfg_t ADC_Service_AdcHwCfg_data[ADC_Service_ADC_COUNT];

inline void ADC_Service_AdcHwCfg_data_INIT_FUNC(void)
{
    ADC_Service_AdcHwCfg_data[ADC_Service_ADC_0_ID].pu8AdcBuffer = &ADC_Service_ADC_0_Buffer[0];
    ADC_Service_AdcHwCfg_data[ADC_Service_ADC_0_ID].u8AdcBufferSize = ADC_Service_ADC_0_BUFFER_SIZE;
    ADC_Service_AdcHwCfg_data[ADC_Service_ADC_0_ID].status = RET_NOT_OK;
}