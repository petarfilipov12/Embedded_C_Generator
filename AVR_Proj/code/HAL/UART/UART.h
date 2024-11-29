#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include "Types.h"

extern void UART_Init(uint16 ubrr);
extern void UART_putc(uint8 data);

#endif