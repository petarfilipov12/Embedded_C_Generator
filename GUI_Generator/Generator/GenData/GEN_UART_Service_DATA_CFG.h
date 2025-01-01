#ifndef GEN_UART_SERVICE_DATA_CFG_H
#define GEN_UART_SERVICE_DATA_CFG_H

#include "Types.h"
#include "Queue.h"
#include "GEN_UART_Service_CFG.h"

extern UART_Service_UartHwCfg_t UART_Service_UartHwCfg_data[UART_Service_UART_Service_UARTs_Count];

extern inline void UART_Service_UartHwCfg_data_INIT_FUNC(void);

#endif