#include "GEN_UART_Service_DATA_CFG.h"

uint8 UART_Service_UART_0_uartRxBuffer[UART_Service_UART_0_UartRxBufferSize];
uint8 UART_Service_UART_0_uartTxBuffer[UART_Service_UART_0_UartTxBufferSize];

UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_Service_UARTs_Count];

inline void UART_Service_UartHwCfg_data_INIT_FUNC(void)
{
	UART_Service_UartHwCfg_data[0].baud = UART_Service_UART_0_Baud;
	UART_Service_UartHwCfg_data[0].id = UART_Service_UART_0_Id;
	UART_Service_UartHwCfg_data[0].uartRxBuffer = &UART_Service_UART_0_uartRxBuffer[0];
	UART_Service_UartHwCfg_data[0].uartRxBufferSize = UART_Service_UART_0_UartRxBufferSize;
	UART_Service_UartHwCfg_data[0].uartTxBuffer = &UART_Service_UART_0_uartTxBuffer[0];
	UART_Service_UartHwCfg_data[0].uartTxBufferSize = UART_Service_UART_0_UartTxBufferSize;
	UART_Service_UartHwCfg_data[0].status = RET_NOT_OK;
}