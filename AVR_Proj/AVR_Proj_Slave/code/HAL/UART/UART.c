#include "UART.h"
#include "UART_Service.h"

Func_ReturnType UART_Init(uint8 uart_id, uint16 ubrr)
{
    UBRR0H = (uint8)(ubrr >> 8);
    UBRR0L = (uint8)ubrr;

    UCSR0B = 0u;
    //Enable receiver
    UCSR0B |= (1 << RXEN0);
    //Enable Transmitter
    UCSR0B |= (1 << TXEN0);

    //Enable Rx Interrupt
    UCSR0B |= (1 << RXCIE0);

    UCSR0C = (3 << UCSZ00);

    return RET_OK;
}

Func_ReturnType UART_putc(uint8 uart_id, uint8 data)
{
    Func_ReturnType ret = RET_BUSY;

    if(UCSR0A & (1 << UDRE0))
    {
        UDR0 = data;
        ret = RET_OK;
    }

    return ret;
}

ISR(USART_RX_vect)
{
    UART_Service_UART_Receive(UART_Service_UART_0_ID, &UDR0, 1u);
}