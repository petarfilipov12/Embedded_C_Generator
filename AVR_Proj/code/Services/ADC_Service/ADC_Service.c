#include "ADC_Service.h"

typedef struct{
    Func_ReturnType status;
}ADC_Service_AdcCfg_t;

ADC_Service_AdcCfg_t ADC_Service_Adc_data[ADC_Service_ADC_COUNT] = {
    {RET_NOT_OK}, //ADC_0
};

typedef struct{
    uint8 adc_id;
    Func_ReturnType status;
}ADC_Service_PinCfg_t;

ADC_Service_PinCfg_t ADC_Service_Pin_data[ADC_Service_PIN_COUNT] = {
    {ADC_Service_ADC_0_ID, RET_OK}, //ADC_PIN_0
};

void ADC_Service_Init(void)
{
    uint8 i = 0;

    for(i=0; i<ADC_Service_ADC_COUNT; i++)
    {
        ADC_Service_Adc_data[i].status = ADC_Enable_ADC(i);
    }
}

Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = ADC_Service_Pin_data[pin_id].status;

    if(RET_OK == returnL)
    {
        returnL = ADC_Service_Adc_data[ADC_Service_Pin_data[pin_id].adc_id].status;
        if(RET_OK == returnL)
        {
            returnL = ADC_Start_Measurement(ADC_Service_Pin_data[pin_id].adc_id, pin_id);
            if(RET_OK == returnL)
            {
                ADC_Service_Adc_data[ADC_Service_Pin_data[pin_id].adc_id].status = RET_BUSY;
                ADC_Service_Pin_data[pin_id].status = RET_PENDING;
                returnL = RET_PENDING;
            }
        }
    }

    if(RET_PENDING == returnL)
    {
        if(ADC_IS_ADC_READY(ADC_Service_Pin_data[pin_id].adc_id))
        {
            ADC_READ(ADC_Service_Pin_data[pin_id].adc_id, &value[0]);

            ADC_Service_Adc_data[ADC_Service_Pin_data[pin_id].adc_id].status = RET_OK;
            ADC_Service_Pin_data[pin_id].status = RET_OK;
            returnL = RET_OK;
        }
    }

    return returnL;
}