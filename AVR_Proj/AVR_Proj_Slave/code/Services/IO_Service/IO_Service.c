#include "IO_Service.h"
#include "GPIO.h"

#if IO_Service_PIN_COUNT > 0
typedef struct{
    IO_Service_PinInputOutputType pin_type;
    Func_ReturnType status;
}IO_Service_PinCfg_t;

IO_Service_PinCfg_t IO_Service_Pin_data[IO_Service_PIN_COUNT] = {
    {IO_Service_PIN_0_TYPE, RET_NOT_OK}, //PIN_0
    {IO_Service_PIN_1_TYPE, RET_NOT_OK}  //PIN_1
};
#endif

void IO_Service_Init(void)
{
#if IO_Service_PIN_COUNT > 0    
    uint8 pin_id = 0;

    for(pin_id=0; pin_id<IO_Service_PIN_COUNT; pin_id++)
    {
        IO_Service_Pin_data[pin_id].status = GPIO_Init_PIN(pin_id, IO_Service_Pin_data[pin_id].pin_type);
    }
#endif
}

Func_ReturnType IO_Service_Read_Pin(uint8 pin_id, uint8* value)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if IO_Service_PIN_COUNT > 0
    if((RET_OK == IO_Service_Pin_data[pin_id].status) && (IO_Service_PIN_INPUT == IO_Service_Pin_data[pin_id].pin_type))
    {
        *value = GPIO_READ_PIN(pin_id);
        returnL = RET_OK;
    }
#endif

    return returnL;
}

Func_ReturnType IO_Service_Set_Pin(uint8 pin_id, IO_Service_PinStateType pin_state)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if IO_Service_PIN_COUNT > 0
    if( (RET_OK == IO_Service_Pin_data[pin_id].status) && (IO_Service_PIN_OUTPUT == IO_Service_Pin_data[pin_id].pin_type) )
    {
        if(IO_Service_PIN_LOW == pin_state)
        {
            GPIO_SET_PIN_LOW(pin_id);
            returnL = RET_OK;
        }
        else if (IO_Service_PIN_HIGH == pin_state)
        {
            GPIO_SET_PIN_HIGH(pin_id);
            returnL = RET_OK;
        }
        else
        {
            //Wrong Pin State
        }
    }
#endif

    return returnL;
}

Func_ReturnType IO_Service_Toggle_Pin(uint8 pin_id)
{
    Func_ReturnType returnL = RET_NOT_OK;

#if IO_Service_PIN_COUNT > 0
    if((RET_OK == IO_Service_Pin_data[pin_id].status) && (IO_Service_PIN_OUTPUT == IO_Service_Pin_data[pin_id].pin_type))
    {
        GPIO_TOGGLE_PIN(pin_id);
        returnL = RET_OK;
    }
#endif

    return returnL;
}