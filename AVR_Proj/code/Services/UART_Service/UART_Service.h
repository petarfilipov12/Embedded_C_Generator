#ifndef UART_SERVICE_H
#define UART_SERVICE_H

#include "Queue.h"
#include "UART.h"
#include "SystemConfig.h"

#define BAUD                9600UL
#define CALC_UBRR(baud)     (((F_CPU / (16 * baud)) - 1))

#define UART_Service_UART_TX_BUFFER_SIZE    50u
#define UART_Service_UART_RX_BUFFER_SIZE    50u
#define UART_Service_UART_0_ID  0u
#define UART_Service_UART_HW_COUNT       1u

typedef struct{
    Queue_t sUartTxQueue;
    Queue_t sUartRxQueue;
    uint8 au8UartTxBuffer[UART_Service_UART_TX_BUFFER_SIZE];
    uint8 au8UartRxBuffer[UART_Service_UART_RX_BUFFER_SIZE];
    Func_ReturnType status;
}UART_Service_UartHwCfg_t;

UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_HW_COUNT];

extern Func_ReturnType UART_Service_Transmit(uint8 uart_id, uint8* data, uint8 data_length);
extern inline void UART_Service_UART_Receive(uint8 uart_id, uint8* data, uint8 data_length);
extern Func_ReturnType UART_Service_Read(uint8 uart_id, uint8* data, uint8 *data_length);

#endif