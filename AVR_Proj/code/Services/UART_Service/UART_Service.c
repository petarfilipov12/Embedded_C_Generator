#include "UART_Service.h"
#include "Queue.h"

typedef struct UartQueue{
    Queue_t sUartQueue;
    uint8 au8UartBuffer[UART_BUFFER_SIZE];
    boolean in_use;
}UartQueue_t;

#define UART_Service_Queue_FREE      0
#define UART_Service_Queue_IN_USE    1

UartQueue_t gUartQueue;

void UART_Service_Init(void)
{
    Queue_Init(&gUartQueue.sUartQueue, &gUartQueue.au8UartBuffer[0], UART_BUFFER_SIZE);
    gUartQueue.in_use = UART_Service_Queue_FREE;

    UART_Init(CALC_UBRR(BAUD));
}

Func_ReturnType UART_Service_Transmit(uint8* data, uint8 data_length)
{
    Func_ReturnType ret = RET_QUEUE_IN_USE;

    if(gUartQueue.in_use == UART_Service_Queue_FREE)
    {
        gUartQueue.in_use = UART_Service_Queue_IN_USE;
        ret = Queue_Put(&gUartQueue.sUartQueue, &data[0], data_length);
        gUartQueue.in_use = UART_Service_Queue_FREE;
    }

    return ret;
}

void UART_Service_Cyclic(void)
{
    uint8 value = 0;
    Func_ReturnType ret = RET_NOT_OK;

    if(Queue_IsEmpty(&gUartQueue.sUartQueue) != TRUE)
    {
        ret = Queue_Pop(&gUartQueue.sUartQueue, &value);

        if(ret == RET_OK)
        {
            UART_putc(value);
        }
    }
}