#include "GEN_UART_Service_DATA_CFG.h"

uint8 UART_Service_UART_0_UartRxBuffer[UART_Service_UART_0_UartRxBufferSize];
uint8 UART_Service_UART_0_UartTxBuffer[UART_Service_UART_0_UartTxBufferSize];

UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_Service_UARTs_Count];

inline void UART_Service_UartHwCfg_data_INIT_FUNC(void)
{
	UART_Service_UartHwCfg_data[0].baud = UART_Service_UART_0_Baud;
	UART_Service_UartHwCfg_data[0].id = UART_Service_UART_0_Id;
	UART_Service_UartHwCfg_data[0].UartRxBuffer = &UART_Service_UART_0_UartRxBuffer[0];
	UART_Service_UartHwCfg_data[0].UartRxBufferSize = UART_Service_UART_0_UartRxBufferSize;
	UART_Service_UartHwCfg_data[0].UartTxBuffer = &UART_Service_UART_0_UartTxBuffer[0];
	UART_Service_UartHwCfg_data[0].UartTxBufferSize = UART_Service_UART_0_UartTxBufferSize;
	UART_Service_UartHwCfg_data[0].status = RTE_NOT_OK;
}