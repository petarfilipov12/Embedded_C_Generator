#ifndef UART_SERVICE_H
#define UART_SERVICE_H

#include "UART.h"
#include "SystemConfig.h"

#define BAUD                9600UL
#define CALC_UBRR(baud)     (((F_CPU / (16 * baud)) - 1))

#define UART_Service_UART_BUFFER_SIZE    200u
#define UART_Service_UART_0_ID  0u
#define UART_Service_UART_HW_COUNT       1u

extern Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length);

#endif