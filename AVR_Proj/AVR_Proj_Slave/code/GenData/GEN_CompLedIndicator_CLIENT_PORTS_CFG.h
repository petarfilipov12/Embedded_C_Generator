#ifndef GEN_COMPLEDINDICATOR_CLIENT_PORTS_CFG_H
#define GEN_COMPLEDINDICATOR_CLIENT_PORTS_CFG_H

#include "GEN_SPI_Service_SERVER_PORTS_CFG.h"
#include "GEN_SPI_Service_CFG.h"
#include "GEN_UART_Service_SERVER_PORTS_CFG.h"
#include "GEN_UART_Service_CFG.h"
#include "GEN_LCD_Driver_SERVER_PORTS_CFG.h"

#define CompLedIndicator_SPI_Get_Received	SPI_Service_GetReceived
#define CompLedIndicator_UART_Transmit	UART_Service_Transmit
#define CompLedIndicator_LCD_Begin	LCD_Driver_LCD_Begin
#define CompLedIndicator_LCD_Clear	LCD_Driver_LCD_Clear
#define CompLedIndicator_LCD_SetCursor	LCD_Driver_LCD_SetCursor
#define CompLedIndicator_LCD_WriteString	LCD_Driver_LCD_WriteString
#define CompLedIndicator_LCD_WriteNumber	LCD_Driver_LCD_WriteNumber
#define CompLedIndicator_LCD_Status	LCD_Driver_LCD_Status

#endif