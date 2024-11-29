#include "UART_Service.h"


void UART_Service_Init(void)
{
    UART_Init(CALC_UBRR(BAUD));
}

void UART_Service_Transmit(uint8* data, uint8 data_length)
{
    uint8 i = 0;

    for(i=0; i<data_length; i++)
    {
        UART_putc(data[i]);
    }
}