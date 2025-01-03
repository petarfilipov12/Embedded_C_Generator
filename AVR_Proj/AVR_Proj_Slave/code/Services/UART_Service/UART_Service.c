#include "UART_Service.h"
#include "GEN_UART_Service_DATA_CFG.h"
#include "UART.h"

void UART_Service_Init(void)
{
#if UART_Service_UART_Service_UARTs_Count > 0
    uint8 uart_id = 0;

    UART_Service_UartHwCfg_data_INIT_FUNC();

    for(uart_id = 0; uart_id < UART_Service_UART_Service_UARTs_Count; uart_id++)
    {
        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].uartTxQueue,
            &UART_Service_UartHwCfg_data[uart_id].uartTxBuffer[0],
            UART_Service_UartHwCfg_data[uart_id].uartTxBufferSize
        );

        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].uartRxQueue,
            &UART_Service_UartHwCfg_data[uart_id].uartRxBuffer[0],
            UART_Service_UartHwCfg_data[uart_id].uartRxBufferSize
        );

        UART_Service_UartHwCfg_data[uart_id].status = UART_Init(uart_id, CALC_UBRR(UART_Service_UartHwCfg_data[uart_id].baud));
    }
#endif
}

void UART_Service_Cyclic(void)
{
#if UART_Service_UART_Service_UARTs_Count > 0
    uint8 uart_id = 0;
    uint8 value = 0;

    for(uart_id = 0; uart_id < UART_Service_UART_Service_UARTs_Count; uart_id++)
    {
        if( (RET_NOT_OK != UART_Service_UartHwCfg_data[uart_id].status)
            && (RET_OK == Queue_Peek(&UART_Service_UartHwCfg_data[uart_id].uartTxQueue, &value))
            && (RET_OK == UART_putc(uart_id, value)) )
        {
            (void)Queue_Pop(&UART_Service_UartHwCfg_data[uart_id].uartTxQueue, NULL);
        }
    }
#endif
}

Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if UART_Service_UART_Service_UARTs_Count > 0
    ret = UART_Service_UartHwCfg_data[uart_id].status;

    if(RET_OK == ret)
    {
        UART_Service_UartHwCfg_data[uart_id].status = RET_BUSY;
        ret = Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].uartTxQueue, &data[0], data_length);
        UART_Service_UartHwCfg_data[uart_id].status = ret;
    }
#endif

    return ret;
}

Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8 *data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if UART_Service_UART_Service_UARTs_Count > 0
    uint8 i = 0;

    ret = UART_Service_UartHwCfg_data[uart_id].status;
    

    *data_length = 0;

    if(RET_NOT_OK != ret)
    {
        if(Queue_IsEmpty(&UART_Service_UartHwCfg_data[uart_id].uartRxQueue))
        {
            ret = RET_QUEUE_EMPTY;
        }
        else
        {
            for(i=0; RET_OK == Queue_Pop(&UART_Service_UartHwCfg_data[uart_id].uartRxQueue, &data[i]); i++);
            *data_length = i;
        }
    }
#endif

    return ret;
}

//Ment to be called from HAL as Rx interrupt
inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length)
{
#if UART_Service_UART_Service_UARTs_Count > 0
    if(RET_OK == UART_Service_UartHwCfg_data[uart_id].status)
    {
        (void)Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].uartRxQueue, &data[0], data_length);
    }
#endif
}