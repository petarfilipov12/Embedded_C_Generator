#include "Types.h"
#include "GPIO.h"

GPIO_sPinDataCfg_t asGPIOPinsCfg[eGPIO_count] = {GPIO_PinDataCfg_INIT};

Func_ReturnType HAL_GPIO_Init_PIN(uint8 pin_id, GPIO_PinInputOutputType pin_type)
{
    Func_ReturnType returnL = RET_OK;

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
        returnL = RET_NOT_OK;
    }

    return returnL;
}