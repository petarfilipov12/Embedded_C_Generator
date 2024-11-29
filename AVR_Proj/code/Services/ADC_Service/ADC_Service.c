#include "ADC_Service.h"

void ADC_Service_Init(void)
{
    if(ADC_Service_PIN_COUNT > 0)
    {
        ADC_Enable_ADC();
    }
}

Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = RET_BUSY;

    if(ADC_IS_ADC_READY())
    {
        if(RET_OK == ADC_Start_Measurement(pin_id))
        {
            while(!ADC_IS_ADC_READY())
            {
                //Wait for measurement to finish
            }

            ADC_READ(value);

            returnL = RET_OK;
        }
    }

    return returnL;
}