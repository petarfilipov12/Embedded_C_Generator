#ifndef GEN_DATA_CFG_UART_SERVICE_H
#define GEN_DATA_CFG_UART_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_UART_Service_CFG.h"

typedef struct{
    Queue_t sUartTxQueue;
    Queue_t sUartRxQueue;
    uint32 baud;
    uint8* pu8UartTxBuffer;
    uint8 u8UartTxBufferSize;
    uint8* pu8UartRxBuffer;
    uint8 u8UartRxBufferSize;
    Func_ReturnType status;
}UART_Service_UartHwCfg_t;

extern UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_HW_COUNT];

extern inline void UART_Service_UartHwCfg_data_INIT_FUNC(void);

#endif