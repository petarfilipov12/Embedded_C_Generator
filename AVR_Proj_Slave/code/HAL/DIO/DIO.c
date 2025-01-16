#include "Types.h"
#include "DIO.h"

#if DIO_PIN_COUNT > 0
DIO_sPinDataCfg_t asDIOPinsCfg[DIO_PIN_COUNT] = {DIO_PinDataCfg_INIT};
#endif

Func_ReturnType DIO_Init_PIN(uint8 pin_id, uint8 pin_type)
{
#if DIO_PIN_COUNT > 0
    Func_ReturnType returnL = RET_OK;

    if(DIO_PIN_INPUT == pin_type)
    {
        DIO_SET_PIN_AS_INPUT(pin_id);
        DIO_SET_PIN_PULL_UP(pin_id);
    }
    else if(DIO_PIN_OUTPUT == pin_type)
    {
        DIO_SET_PIN_AS_OUTPUT(pin_id);
    }
    else
    {
        //Error should not be here
        returnL = RET_NOT_OK;
    }

    return returnL;
#else
    return RET_NOT_OK;
#endif
}