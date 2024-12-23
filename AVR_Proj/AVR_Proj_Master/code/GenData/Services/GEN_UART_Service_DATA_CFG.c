#include "GEN_UART_Service_DATA_CFG.h"

uint8 UART_Service_UART_0_TxBuffer[UART_Service_UART_0_TX_BUFFER_SIZE];
uint8 UART_Service_UART_0_RxBuffer[UART_Service_UART_0_RX_BUFFER_SIZE];

UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_HW_COUNT];

inline void UART_Service_UartHwCfg_data_INIT_FUNC(void)
{
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].baud = UART_Service_UART_0_BAUD;
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].pu8UartTxBuffer = &UART_Service_UART_0_TxBuffer[0];
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].u8UartTxBufferSize = UART_Service_UART_0_TX_BUFFER_SIZE;
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].pu8UartRxBuffer = &UART_Service_UART_0_RxBuffer[0];
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].u8UartRxBufferSize = UART_Service_UART_0_RX_BUFFER_SIZE;
    UART_Service_UartHwCfg_data[UART_Service_UART_0_ID].status = RET_NOT_OK;
}