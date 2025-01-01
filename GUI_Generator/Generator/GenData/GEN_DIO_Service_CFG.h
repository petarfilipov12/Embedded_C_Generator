#ifndef GEN_DIO_SERVICE_CFG_H
#define GEN_DIO_SERVICE_CFG_H

#include "Types.h"

#define DIO_Service_DIO_Service_Pins_Count 2

#define DIO_Service_DIO_PIN_0_Id 0
#define DIO_Service_DIO_PIN_0_PinInitState LOW
#define DIO_Service_DIO_PIN_0_PinType OUTPUT

#define DIO_Service_DIO_PIN_1_Id 1
#define DIO_Service_DIO_PIN_1_PinInitState LOW
#define DIO_Service_DIO_PIN_1_PinType INPUT


#define DIO_Service_Data_Init \
/* DIO_PIN_0 */{DIO_Service_DIO_PIN_0_Id, DIO_Service_DIO_PIN_0_PinInitState, DIO_Service_DIO_PIN_0_PinType, RET_NOT_OK}, \
/* DIO_PIN_1 */{DIO_Service_DIO_PIN_1_Id, DIO_Service_DIO_PIN_1_PinInitState, DIO_Service_DIO_PIN_1_PinType, RET_NOT_OK}

#endif