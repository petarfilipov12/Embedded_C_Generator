#ifndef UART_SERVICE_H
#define UART_SERVICE_H

#include "Types.h"
#include "SystemConfig.h"
#include "GEN_UART_Service_CFG.h"

#define CALC_UBRR(baud)     (((F_CPU / (16 * baud)) - 1))

extern Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length);
extern inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length);
extern Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8 *data_length);

#endif