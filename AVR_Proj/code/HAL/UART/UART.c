#include "UART.h"

Func_ReturnType UART_Init(uint8 uart_id, uint16 ubrr)
{
    UBRR0H = (uint8)(ubrr >> 8);
    UBRR0L = (uint8)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (3 << UCSZ00);

    return RET_OK;
}

Func_ReturnType UART_putc(uint8 uart_id, uint8 data)
{
    while(!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;

    return RET_OK;
}