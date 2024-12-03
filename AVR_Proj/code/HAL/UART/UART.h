#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include "Types.h"

extern Func_ReturnType UART_Init(uint8 uart_id, uint16 ubrr);
extern Func_ReturnType UART_putc(uint8 uart_id, uint8 data);

#endif