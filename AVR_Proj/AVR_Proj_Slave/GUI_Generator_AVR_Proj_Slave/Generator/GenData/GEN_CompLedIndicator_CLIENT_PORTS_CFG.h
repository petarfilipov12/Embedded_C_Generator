#ifndef GEN_COMPLEDINDICATOR_CLIENT_PORTS_CFG_H
#define GEN_COMPLEDINDICATOR_CLIENT_PORTS_CFG_H

#include "GEN_PWM_Service_SERVER_PORTS_CFG.h"
#include "GEN_PWM_Service_CFG.h"
#include "GEN_SPI_Service_SERVER_PORTS_CFG.h"
#include "GEN_SPI_Service_CFG.h"
#include "GEN_UART_Service_SERVER_PORTS_CFG.h"
#include "GEN_UART_Service_CFG.h"

#define CompLedIndicator_PWM_Set_Pin	PWM_Service_Set_Pin
#define CompLedIndicator_SPI_Get_Received	SPI_Service_GetReceived
#define CompLedIndicator_UART_Transmit	UART_Service_Transmit

#endif