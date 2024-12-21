#include "UART_Service.h"

void UART_Service_Init(void)
{
    uint8 uart_id = 0;

    for(uart_id=0; uart_id<UART_Service_UART_HW_COUNT; uart_id++)
    {
        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].sUartTxQueue,
            &UART_Service_UartHwCfg_data[uart_id].au8UartTxBuffer[0],
            UART_Service_UART_TX_BUFFER_SIZE
        );

        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].sUartRxQueue,
            &UART_Service_UartHwCfg_data[uart_id].au8UartRxBuffer[0],
            UART_Service_UART_RX_BUFFER_SIZE
        );

        UART_Service_UartHwCfg_data[uart_id].status = UART_Init(uart_id, CALC_UBRR(BAUD));
    }
}

Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length)
{
    Func_ReturnType ret = UART_Service_UartHwCfg_data[uart_id].status;

    if(RET_OK == ret)
    {
        UART_Service_UartHwCfg_data[uart_id].status = RET_BUSY;
        ret = Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].sUartTxQueue, &data[0], data_length);
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
            && (RET_OK == Queue_Peek(&UART_Service_UartHwCfg_data[uart_id].sUartTxQueue, &value))
            && (RET_OK == UART_putc(uart_id, value)) )
        {
            (void)Queue_Pop(&UART_Service_UartHwCfg_data[uart_id].sUartTxQueue, NULL);
        }
    }
}

//Ment to be called from HAL as Rx interrupt
inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length)
{
    if(RET_OK == UART_Service_UartHwCfg_data[uart_id].status)
    {
        (void)Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].sUartRxQueue, &data[0], data_length);
    }
}

Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8 *data_length)
{
    Func_ReturnType ret = UART_Service_UartHwCfg_data[uart_id].status;
    uint8 i = 0;

    *data_length = 0;

    if(RET_NOT_OK != ret)
    {
        if(Queue_IsEmpty(&UART_Service_UartHwCfg_data[uart_id].sUartRxQueue))
        {
            ret = RET_QUEUE_EMPTY;
        }
        else
        {
            for(i=0; RET_OK == Queue_Pop(&UART_Service_UartHwCfg_data[uart_id].sUartRxQueue, &data[i]); i++);
            *data_length = i;
        }
    }

    return ret;
}