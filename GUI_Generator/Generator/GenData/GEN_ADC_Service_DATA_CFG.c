#include "GEN_ADC_Service_DATA_CFG.h"

uint8 ADC_Service_ADC_0_AdcBuffer[ADC_Service_ADC_0_AdcBufferSize];

ADC_Service_AdcCfg_t ADC_Service_AdcHwCfg_data[ADC_Service_ADC_Service_ADCs_Count];

inline void ADC_Service_AdcHwCfg_data_INIT_FUNC(void)
{
	ADC_Service_AdcHwCfg_data[0].AdcBuffer = &ADC_Service_ADC_0_AdcBuffer[0];
	ADC_Service_AdcHwCfg_data[0].AdcBufferSize = ADC_Service_ADC_0_AdcBufferSize;
	ADC_Service_AdcHwCfg_data[0].id = ADC_Service_ADC_0_Id;
	ADC_Service_AdcHwCfg_data[0].status = RTE_NOT_OK;

ADC_Service_PinCfg_t ADC_Service_AdcPinCfg_data[ADC_Service_ADC_Service_Pins_Count];

inline void ADC_Service_AdcPinCfg_data_INIT_FUNC(void)
{
	ADC_Service_AdcPinCfg_data[0].adcref = ADC_Service_ADC_PIN_0_AdcRef;
	ADC_Service_AdcPinCfg_data[0].id = ADC_Service_ADC_PIN_0_Id;
	ADC_Service_AdcPinCfg_data[0].status = RTE_NOT_OK;
}