#include "ADC_Service.h"
#include "ADC.h"


typedef struct{
    uint8 current_pin_id;
    Queue_t sAdcQueue;
    uint8 au8AdcBuffer[ADC_Service_ADC_BUFFER_SIZE];
    Func_ReturnType status;
}ADC_Service_AdcCfg_t;

typedef struct{
    uint8 adc_id;
    uint8 last_value;
    Func_ReturnType status;
}ADC_Service_PinCfg_t;

#if ADC_Service_ADC_COUNT > 0
ADC_Service_AdcCfg_t ADC_Service_Adc_data[ADC_Service_ADC_COUNT];
#endif

#if ADC_Service_PIN_COUNT > 0
ADC_Service_PinCfg_t ADC_Service_Pin_data[ADC_Service_PIN_COUNT] = {ADC_Service_Pin_data_INIT};
#endif

void ADC_Service_Init(void)
{
#if ADC_Service_ADC_COUNT > 0
    uint8 i = 0;

    for(i=0; i<ADC_Service_ADC_COUNT; i++)
    {
        Queue_Init(&ADC_Service_Adc_data[i].sAdcQueue, &ADC_Service_Adc_data[i].au8AdcBuffer[0], ADC_Service_ADC_BUFFER_SIZE);
        ADC_Service_Adc_data[i].status = ADC_Enable_ADC(i);
    }
#endif
}

void ADC_Service_Cyclic(void)
{
#if (ADC_Service_ADC_COUNT > 0) && (ADC_Service_PIN_COUNT > 0)
    uint8 adc_id = 0;
    uint8 pin_id = 0;

    for(adc_id=0; adc_id<ADC_Service_ADC_COUNT; adc_id++)
    {
        if(RET_OK == ADC_Service_Adc_data[adc_id].status)
        {
            if(!Queue_IsEmpty(&ADC_Service_Adc_data[adc_id].sAdcQueue))
            {
                if(RET_OK == Queue_Pop(&ADC_Service_Adc_data[adc_id].sAdcQueue, &pin_id))
                {
                    if(RET_OK == ADC_Start_Measurement(adc_id, pin_id))
                    {
                        ADC_Service_Adc_data[adc_id].current_pin_id = pin_id;
                        ADC_Service_Adc_data[adc_id].status = RET_BUSY;
                        ADC_Service_Pin_data[pin_id].status = RET_PENDING;
                    }
                    else
                    {
                        Queue_PutData(&ADC_Service_Adc_data[adc_id].sAdcQueue, &pin_id, 1u);
                    }
                }
            }
        }
        else if(RET_BUSY == ADC_Service_Adc_data[adc_id].status)
        {
            if(ADC_IS_ADC_READY(adc_id))
            {
                ADC_READ(adc_id, &ADC_Service_Pin_data[ADC_Service_Adc_data[adc_id].current_pin_id].last_value);
                ADC_Service_Adc_data[adc_id].status = RET_OK;
                ADC_Service_Pin_data[ADC_Service_Adc_data[adc_id].current_pin_id].status = RET_READY;
            }
        }
    }
#endif
}

Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = RET_NOT_OK;
    
#if ADC_Service_PIN_COUNT > 0
    returnL = ADC_Service_Pin_data[pin_id].status;

    if(RET_OK == returnL)
    {
         returnL = ADC_Service_Adc_data[ADC_Service_Pin_data[pin_id].adc_id].status;
        if(RET_NOT_OK != returnL)
        {
            returnL = Queue_PutData(&ADC_Service_Adc_data[ADC_Service_Pin_data[pin_id].adc_id].sAdcQueue, &pin_id, 1u);
            if(RET_OK == returnL)
            {
                ADC_Service_Pin_data[pin_id].status = RET_PENDING;
                returnL = RET_PENDING;
            }
        }
    }
    else if(RET_READY == returnL)
    {
        *value = ADC_Service_Pin_data[pin_id].last_value;
        ADC_Service_Pin_data[pin_id].status = RET_OK;
        returnL = RET_OK;
    }
#endif

    return returnL;
}