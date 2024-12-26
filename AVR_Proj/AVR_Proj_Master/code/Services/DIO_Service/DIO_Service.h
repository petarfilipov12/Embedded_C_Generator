#ifndef DIO_SERVICE_H
#define DIO_SERVICE_H

#include "Types.h"
#include "GEN_DIO_Service_CFG.h"

#define DIO_Service_PIN_INPUT            0u
#define DIO_Service_PIN_OUTPUT           1u

#define DIO_Service_PIN_LOW              0u
#define DIO_Service_PIN_HIGH             1u

extern Func_ReturnType DIO_Service_Set_Pin(uint8 pin_id, uint8 pin_type);
extern Func_ReturnType DIO_Service_Read_Pin(uint8 pin_id, uint8* value);
extern Func_ReturnType DIO_Service_Write_Pin(uint8 pin_id, uint8 pin_state);
extern Func_ReturnType DIO_Service_Toggle_Pin(uint8 pin_id);

#endif