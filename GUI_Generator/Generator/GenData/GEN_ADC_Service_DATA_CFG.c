#include "GEN_ADC_Service_DATA_CFG.h"

uint8 ADC_Service_ADC_0_adcBuffer[ADC_Service_ADC_0_AdcBufferSize];

ADC_Service_AdcCfg_t ADC_Service_AdcHwCfg_data[ADC_Service_ADC_Service_ADCs_Count];

inline void ADC_Service_AdcHwCfg_data_INIT_FUNC(void)
{
	ADC_Service_AdcHwCfg_data[0].adcBuffer = &ADC_Service_ADC_0_adcBuffer[0];
	ADC_Service_AdcHwCfg_data[0].adcBufferSize = ADC_Service_ADC_0_AdcBufferSize;
	ADC_Service_AdcHwCfg_data[0].id = ADC_Service_ADC_0_Id;
	ADC_Service_AdcHwCfg_data[0].status = RET_NOT_OK;
}

ADC_Service_PinCfg_t ADC_Service_AdcPinCfg_data[ADC_Service_ADC_Service_Pins_Count];

inline void ADC_Service_AdcPinCfg_data_INIT_FUNC(void)
{
	ADC_Service_AdcPinCfg_data[0].adcRef = ADC_Service_ADC_PIN_0_AdcRef;
	ADC_Service_AdcPinCfg_data[0].id = ADC_Service_ADC_PIN_0_Id;
	ADC_Service_AdcPinCfg_data[0].status = RET_NOT_OK;
}