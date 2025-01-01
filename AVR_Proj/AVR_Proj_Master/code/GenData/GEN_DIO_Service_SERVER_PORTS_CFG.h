#ifndef GEN_DIO_SERVICE_SERVER_PORTS_CFG_H
#define GEN_DIO_SERVICE_SERVER_PORTS_CFG_H

#include "Types.h"
#include "Queue.h"

extern Func_ReturnType DIO_Service_Set_Pin(uint8 pin_id, uint8 pin_type);
extern Func_ReturnType DIO_Service_Read_Pin(uint8 pin_id, uint8* value);
extern Func_ReturnType DIO_Service_Write_Pin(uint8 pin_id, uint8 pin_state);
extern Func_ReturnType DIO_Service_Toggle_Pin(uint8 pin_id);

#endif