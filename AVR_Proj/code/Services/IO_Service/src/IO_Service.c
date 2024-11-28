#include "IO_Service.h"
#include "GPIO.h"

typedef struct{
    uint8 pin_id;
    IO_Service_PinInputOutputType pin_type;
}PinCfg_t;

PinCfg_t Pin_data[IO_Service_PIN_COUNT] = {
    {IO_Service_PIN_0_ID, IO_Service_PIN_0_TYPE},
    {IO_Service_PIN_1_ID, IO_Service_PIN_1_TYPE}
};

void IO_Service_Init(void)
{
    uint8 i = 0;

    for(i=0; i<IO_Service_PIN_COUNT; i++)
    {
        (void)HAL_GPIO_Init_PIN(Pin_data[i].pin_id, Pin_data[i].pin_type);
    }
}