#include "ADC_Service.h"
#include "GEN_ADC_Service_DATA_CFG.h"
#include "GEN_ADC_Service_SERVER_PORTS_CFG.h"
#include "GEN_ADC_Service_CLIENT_PORTS_CFG.h"
#include "ADC.h"

void ADC_Service_Init(void)
{
#if ADC_Service_ADC_Service_ADCs_Count > 0
    uint8 adc_id = 0;

    ADC_Service_AdcHwCfg_data_INIT_FUNC();

    for(adc_id = 0; adc_id < ADC_Service_ADC_Service_ADCs_Count; adc_id++)
    {
        Queue_Init(
            &ADC_Service_AdcHwCfg_data[adc_id].adcQueue,
            &ADC_Service_AdcHwCfg_data[adc_id].adcBuffer[0],
            ADC_Service_AdcHwCfg_data[adc_id].adcBufferSize
        );

        ADC_Service_AdcHwCfg_data[adc_id].status = ADC_Enable_ADC(adc_id);
    }
#endif

#if ADC_Service_ADC_Service_Pins_Count > 0
    uint8 pin_id = 0;

    ADC_Service_AdcPinCfg_data_INIT_FUNC();

    for(pin_id = 0; pin_id < ADC_Service_ADC_Service_Pins_Count; pin_id++)
    {
        ADC_Service_AdcPinCfg_data[0].lastValue = 0;
        ADC_Service_AdcPinCfg_data[0].status = RET_OK;
    }
#endif
}

void ADC_Service_Cyclic(void)
{
#if (ADC_Service_ADC_Service_ADCs_Count > 0) && (ADC_Service_ADC_Service_Pins_Count > 0)
    uint8 adc_id = 0;
    uint8 pin_id = 0;

    for(adc_id=0; adc_id<ADC_Service_ADC_Service_ADCs_Count; adc_id++)
    {
        if(RET_OK == ADC_Service_AdcHwCfg_data[adc_id].status)
        {
            if(!Queue_IsEmpty(&ADC_Service_AdcHwCfg_data[adc_id].adcQueue))
            {
                if(RET_OK == Queue_Pop(&ADC_Service_AdcHwCfg_data[adc_id].adcQueue, &pin_id))
                {
                    if(RET_OK == ADC_Start_Measurement(adc_id, pin_id))
                    {
                        ADC_Service_AdcHwCfg_data[adc_id].currentPinId = pin_id;
                        ADC_Service_AdcHwCfg_data[adc_id].status = RET_BUSY;
                        ADC_Service_AdcPinCfg_data[pin_id].status = RET_PENDING;
                    }
                    else
                    {
                        Queue_PutData(&ADC_Service_AdcHwCfg_data[adc_id].adcQueue, &pin_id, 1u);
                    }
                }
            }
        }
        else if(RET_BUSY == ADC_Service_AdcHwCfg_data[adc_id].status)
        {
            if(ADC_IS_ADC_READY(adc_id))
            {
                ADC_READ(adc_id, &ADC_Service_AdcPinCfg_data[ADC_Service_AdcHwCfg_data[adc_id].current_pin_id].last_value);
                ADC_Service_AdcHwCfg_data[adc_id].status = RET_OK;
                ADC_Service_AdcPinCfg_data[ADC_Service_AdcHwCfg_data[adc_id].currentPinId].status = RET_READY;
            }
        }
    }
#endif
}

Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = RET_NOT_OK;
    
#if ADC_Service_ADC_Service_Pins_Count > 0
    returnL = ADC_Service_AdcPinCfg_data[pin_id].status;

    if(RET_OK == returnL)
    {
        returnL = ADC_Service_AdcHwCfg_data[ADC_Service_AdcPinCfg_data[pin_id].adcRef].status;
        if(RET_NOT_OK != returnL)
        {
            returnL = Queue_PutData(&ADC_Service_AdcHwCfg_data[ADC_Service_AdcPinCfg_data[pin_id].adcRef].adcQueue, &pin_id, 1u);
            if(RET_OK == returnL)
            {
                ADC_Service_AdcPinCfg_data[pin_id].status = RET_PENDING;
                returnL = RET_PENDING;
            }
        }
    }
    else if(RET_READY == returnL)
    {
        *value = ADC_Service_AdcPinCfg_data[pin_id].lastValue;
        ADC_Service_AdcPinCfg_data[pin_id].status = RET_OK;
        returnL = RET_OK;
    }
#endif

    return returnL;
}