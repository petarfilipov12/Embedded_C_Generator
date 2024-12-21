#ifndef IO_SERVICE_H
#define IO_SERVICE_H

#include "Types.h"
#include "GPIO.h"

#define IO_Service_PinInputOutputType   GPIO_PinInputOutputType
#define IO_Service_PIN_INPUT            GPIO_PIN_INPUT
#define IO_Service_PIN_OUTPUT           GPIO_PIN_OUTPUT

#define IO_Service_PinStateType         GPIO_PinStateType
#define IO_Service_PIN_LOW              GPIO_PIN_LOW
#define IO_Service_PIN_HIGH             GPIO_PIN_HIGH

#define IO_Service_PIN_UNDEFINED        GPIO_PIN_UNDEFINED

/*  Start Pin_data  */
#define IO_Service_PIN_0_ID             0
#define IO_Service_PIN_0_TYPE           IO_Service_PIN_OUTPUT

#define IO_Service_PIN_1_ID             1
#define IO_Service_PIN_1_TYPE           IO_Service_PIN_INPUT

#define IO_Service_PIN_COUNT            2
/*  End Pin_data  */


extern Func_ReturnType IO_Service_Read_Pin(uint8 pin_id, uint8* value);
extern Func_ReturnType IO_Service_Set_Pin(uint8 pin_id, IO_Service_PinStateType pin_state);
extern Func_ReturnType IO_Service_Toggle_Pin(uint8 pin_id);

#endif