#include "ADC_Service.h"

ADC_sPinDataCfg_t asADCPinsCfg[ADC_Service_PIN_COUNT] = {ADC_PinDataCfg_INIT};

void ADC_Service_Init(void)
{
    if(ADC_Service_PIN_COUNT > 0)
    {
        ADC_Enable_ADC();
    }
}

void ADC_Service_Cyclic(void)
{
    uint8 i = 0;

    for(i=0; i<ADC_Service_PIN_COUNT; i++)
    {

    }
}

static inline void ADC_Service_Pin_StateMachine(uint8 pin_id)
{
    switch (asADCPinsCfg[pin_id].state)
    {
    case ADC_PIN_SATE_WAITING_TO_START_MEASUREMENT:
        if(ADC_IS_READY_TO_MEASURE())
        {

        }
        break;

    case ADC_PIN_SATE_MEASURING:
        /* code */
        break;

    case ADC_PIN_SATE_MEASUREMENT_READY:
        /* code */
        break;

    case ADC_PIN_SATE_IDLE:
    default:
        break;
    }
}