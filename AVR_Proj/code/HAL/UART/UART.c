#include "UART.h"

void UART_Init(uint16 ubrr)
{
    UBRR0H = (uint8)(ubrr >> 8);
    UBRR0L = (uint8)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (3 << UCSZ00);
}

void UART_putc(uint8 data)
{
    while(!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
}