/* DO NOT REMOVE COMMENT - GEN INCLUDE SECTION */
#include "GEN_CompLedIndicator_SERVER_PORTS_CFG.h"
#include "GEN_CompLedIndicator_CLIENT_PORTS_CFG.h"
#include "CompLedIndicator.h"
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-VARS SECTION */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-FUNCS SECTION */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN RUNNABLES SECTION */
/* DO NOT REMOVE COMMENT - GEN START FUNC */
void CompLedIndicator_Init(void)
{
  uint8 uart_tx_data[5] = {'I', 'N', 'I', 'T', '\n'};

  UART_Service_Transmit(UART_Service_UART_0_ID, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
void CompLedIndicator_Cyclic(void)
{
  uint8 pin_val = 0;
  uint8 uart_tx_data[7] = {'T', 'O', 'G', 'G', 'L', 'E', '\n'};
  uint8 uart_rx_data[50u];
  uint8 uart_rx_data_length;
  uint8 temp = 0;

  Func_ReturnType ret = RET_OK;

  if( (RET_OK == LedIndicator_Read_Pin(DIO_Service_PIN_1_ID, &pin_val)) && (DIO_Service_PIN_HIGH != pin_val) )
  {
    LedIndicator_Toggle_Pin(DIO_Service_PIN_0_ID);
    UART_Service_Transmit(UART_Service_UART_0_ID, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));
  }
  else
  {
    LedIndicator_Write_Pin(DIO_Service_PIN_0_ID, DIO_Service_PIN_LOW);
  }

  ret = UART_Service_Read(UART_Service_UART_0_ID, &uart_rx_data[0], &uart_rx_data_length);
  if(RET_OK == ret)
  {
    if(uart_rx_data_length > 0)
    {
      UART_Service_Transmit(UART_Service_UART_0_ID, &uart_rx_data[0], uart_rx_data_length);
    }
  }
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */
/* DO NOT REMOVE COMMENT - GEN END SECTION */