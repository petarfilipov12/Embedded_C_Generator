#ifndef UART_SERVICE_H
#define UART_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "SystemConfig.h"
#include "GEN_UART_Service_CFG.h"

#define CALC_UBRR(baud)     (((F_CPU / (16 * baud)) - 1))

typedef struct{
    Queue_t uartRxQueue;
    Queue_t uartTxQueue;
    uint32 baud;
    uint8* uartRxBuffer;
    uint8 uartRxBufferSize;
    uint8* uartTxBuffer;
    uint8 uartTxBufferSize;
    uint8 id;
    Func_ReturnType status;
}UART_Service_UartHwCfg_t;

extern inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length);

#endif