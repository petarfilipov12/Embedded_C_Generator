#ifndef GEN_UART_SERVICE_SERVER_PORTS_CFG_H
#define GEN_UART_SERVICE_SERVER_PORTS_CFG_H

#include "Types.h"
#include "Queue.h"

extern Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length);
extern Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8* data_legth);

#endif