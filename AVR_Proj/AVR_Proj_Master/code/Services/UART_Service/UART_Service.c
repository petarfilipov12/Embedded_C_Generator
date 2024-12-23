#include "UART_Service.h"
#include "GEN_UART_Service_DATA_CFG.h"
#include "UART.h"

void UART_Service_Init(void)
{
#if UART_Service_UART_HW_COUNT > 0
    uint8 uart_id = 0;

    UART_Service_UartHwCfg_data_INIT_FUNC();

    for(uart_id=0; uart_id<UART_Service_UART_HW_COUNT; uart_id++)
    {
        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].sUartTxQueue,
            &UART_Service_UartHwCfg_data[uart_id].pu8UartTxBuffer[0],
            UART_Service_UartHwCfg_data[uart_id].u8UartTxBufferSize
        );

        Queue_Init(
            &UART_Service_UartHwCfg_data[uart_id].sUartRxQueue,
            &UART_Service_UartHwCfg_data[uart_id].pu8UartRxBuffer[0],
            UART_Service_UartHwCfg_data[uart_id].u8UartRxBufferSize
        );

        UART_Service_UartHwCfg_data[uart_id].status = UART_Init(uart_id, CALC_UBRR(UART_Service_UartHwCfg_data[uart_id].baud));
    }
#endif
}

void UART_Service_Cyclic(void)
{
#if UART_Service_UART_HW_COUNT > 0
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
#endif
}

Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if UART_Service_UART_HW_COUNT > 0
    ret = UART_Service_UartHwCfg_data[uart_id].status;

    if(RET_OK == ret)
    {
        UART_Service_UartHwCfg_data[uart_id].status = RET_BUSY;
        ret = Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].sUartTxQueue, &data[0], data_length);
        UART_Service_UartHwCfg_data[uart_id].status = ret;
    }
#endif

    return ret;
}

Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8 *data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if UART_Service_UART_HW_COUNT > 0
    uint8 i = 0;

    ret = UART_Service_UartHwCfg_data[uart_id].status;
    

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
#endif

    return ret;
}

//Ment to be called from HAL as Rx interrupt
inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length)
{
#if UART_Service_UART_HW_COUNT > 0
    if(RET_OK == UART_Service_UartHwCfg_data[uart_id].status)
    {
        (void)Queue_PutData(&UART_Service_UartHwCfg_data[uart_id].sUartRxQueue, &data[0], data_length);
    }
#endif
}