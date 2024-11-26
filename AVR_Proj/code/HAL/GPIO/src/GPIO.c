#include "GPIO.h"

GPIO_sPinDataCfg_t asPinsCfg[eGPIO_count] = {GPIO_PinDataCfg_INIT};

uint8 HAL_GPIO_Init_PIN(uint8 pin_id, GPIO_PinInputOutputType pin_type)
{
    uint8 returnL = FALSE;

    if(GPIO_PIN_INPUT == pin_type)
    {
        GPIO_SET_PIN_AS_INPUT(pin_id);
        GPIO_SET_PIN_PULL_UP(pin_id);
    }
    else if(GPIO_PIN_OUTPUT == pin_type)
    {
        GPIO_SET_PIN_AS_OUTPUT(pin_id);
    }
    else
    {
        //Error should not be here
    }

    return returnL;
}