#include "DIO_Service.h"
#include "GEN_DIO_Service_DATA_CFG.h"
#include "GEN_DIO_Service_SERVER_PORTS_CFG.h"
#include "GEN_DIO_Service_CLIENT_PORTS_CFG.h"
#include "DIO.h"

void DIO_Service_Init(void)
{
#if DIO_Service_DIO_Service_Pins_Count > 0    
    uint8 pin_id = 0;

    DIO_Service_PinCfg_data_INIT_FUNC();

    for(pin_id=0; pin_id<DIO_Service_DIO_Service_Pins_Count; pin_id++)
    {
        DIO_Service_PinCfg_data[pin_id].status = DIO_Init_PIN(pin_id, DIO_Service_PinCfg_data[pin_id].pinType);

        if(PIN_OUTPUT == DIO_Service_PinCfg_data[pin_id].pinType)
        {
            DIO_Service_Write_Pin(pin_id, DIO_Service_PinCfg_data[pin_id].pinState);
        }
    }
#endif
}

Func_ReturnType DIO_Service_Set_Pin(uint8 pin_id, uint8 pinType)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if DIO_Service_DIO_Service_Pins_Count > 0
    if(RET_OK == DIO_Service_PinCfg_data[pin_id].status)
    {
        if(pinType != DIO_Service_PinCfg_data[pin_id].pinType)
        {
            if(PIN_INPUT == pinType)
            {
                DIO_SET_PIN_AS_INPUT(pin_id);
                returnL = RET_OK;
            }
            else if (PIN_OUTPUT == pinType)
            {
                DIO_SET_PIN_AS_OUTPUT(pin_id);
                returnL = RET_OK;
            }
            else
            {
                //Wrong Pin State
            }
        }
        else
        {
            returnL = RET_OK;
        }
    }
#endif

    return returnL;
}

Func_ReturnType DIO_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if DIO_Service_DIO_Service_Pins_Count > 0
    if((RET_OK == DIO_Service_PinCfg_data[pin_id].status) && (PIN_INPUT == DIO_Service_PinCfg_data[pin_id].pinType))
    {
        *value = DIO_READ_PIN(pin_id);
        returnL = RET_OK;
    }
#endif

    return returnL;
}

Func_ReturnType DIO_Service_Write_Pin(uint8 pin_id, uint8 pinState)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if DIO_Service_DIO_Service_Pins_Count > 0
    if( (RET_OK == DIO_Service_PinCfg_data[pin_id].status) && (PIN_OUTPUT == DIO_Service_PinCfg_data[pin_id].pinType) )
    {
        if(pinState != DIO_Service_PinCfg_data[pin_id].pinState)
        {
            if(PIN_LOW == pinState)
            {
                DIO_SET_PIN_LOW(pin_id);
                DIO_Service_PinCfg_data[pin_id].pinState = pinState;
                returnL = RET_OK;
            }
            else if (PIN_HIGH == pinState)
            {
                DIO_SET_PIN_HIGH(pin_id);
                DIO_Service_PinCfg_data[pin_id].pinState = pinState;
                returnL = RET_OK;
            }
            else
            {
                //Wrong Pin State
            }
        }
        else
        {
            returnL = RET_OK;
        }
    }
#endif

    return returnL;
}

Func_ReturnType DIO_Service_Toggle_Pin(uint8 pin_id)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if DIO_Service_DIO_Service_Pins_Count > 0
    if((RET_OK == DIO_Service_PinCfg_data[pin_id].status) && (PIN_OUTPUT == DIO_Service_PinCfg_data[pin_id].pinType))
    {
        if(PIN_LOW == DIO_Service_PinCfg_data[pin_id].pinState)
        {
            DIO_Service_Write_Pin(pin_id, PIN_HIGH);
            returnL = RET_OK;
        }
        else if(PIN_HIGH == DIO_Service_PinCfg_data[pin_id].pinState)
        {
            DIO_Service_Write_Pin(pin_id, PIN_LOW);
            returnL = RET_OK;
        }
        else
        {
            //Should not get here
        }
    }
#endif

    return returnL;
}