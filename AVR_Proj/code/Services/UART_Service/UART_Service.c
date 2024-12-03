#include "UART_Service.h"
#include "Queue.h"

typedef struct{
    Queue_t sUartQueue;
    uint8 au8UartBuffer[UART_Service_UART_BUFFER_SIZE];
    Func_ReturnType status;
}UART_Service_UartHwCfg_t;

UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_HW_COUNT];

void UART_Service_Init(void)
{
    uint8 uart_id = 0;

    for(uart_id=0; uart_id<UART_Service_UART_HW_COUNT; uart_id++)
    {
        Queue_Init(&UART_Service_UartHwCfg_data[uart_id].sUartQueue, &UART_Service_UartHwCfg_data[uart_id].au8UartBuffer[0], UART_Service_UART_BUFFER_SIZE);
        UART_Service_UartHwCfg_data[uart_id].status = UART_Init(uart_id, CALC_UBRR(BAUD));
    }
}

Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length)
{
    Func_ReturnType ret = UART_Service_UartHwCfg_data[uart_id].status;

    if(RET_OK == ret)
    {
        UART_Service_UartHwCfg_data[uart_id].status = RET_BUSY;
        ret = Queue_Put(&UART_Service_UartHwCfg_data[uart_id].sUartQueue, &data[0], data_length);
        UART_Service_UartHwCfg_data[uart_id].status = ret;

    }

    return ret;
}

void UART_Service_Cyclic(void)
{
    uint8 uart_id = 0;
    uint8 value = 0;

    for(uart_id=0; uart_id<UART_Service_UART_HW_COUNT; uart_id++)
    {
        if( (RET_NOT_OK != UART_Service_UartHwCfg_data[uart_id].status)
            && (TRUE != Queue_IsEmpty(&UART_Service_UartHwCfg_data[uart_id].sUartQueue)) 
            && (RET_OK == Queue_Pop(&UART_Service_UartHwCfg_data[uart_id].sUartQueue, &value)) )
        {
            UART_putc(uart_id, value);
        }
    }
}