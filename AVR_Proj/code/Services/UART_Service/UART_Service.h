#ifndef UART_SERVICE_H
#define UART_SERVICE_H

#include "UART.h"
#include "SystemConfig.h"

#define BAUD                9600UL
#define CALC_UBRR(baud)     (((F_CPU / (16 * baud)) - 1))

extern void UART_Service_Transmit(uint8* data, uint8 data_length);

#endif