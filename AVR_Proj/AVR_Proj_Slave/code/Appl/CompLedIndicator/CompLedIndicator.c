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

  CompLedIndicator_PWM_Set_Pin(PWM_Service_PWM_PIN_0_Id, 250);

  CompLedIndicator_UART_Transmit(UART_Service_UART_0_Id, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
void CompLedIndicator_Cyclic(void)
{
  uint8 rx_data[SPI_Service_SPI_0_SpiRxBufferSize] = {0};
  uint8 data_length = 0;
  uint8 avg = 0;
  uint8 i = 0;
  uint32 sum = 0;
  Func_ReturnType ret = RET_OK;

  uint8 uart_tx_data[6] = {'R', 'E', 'T', '=', 'X', '\n'};

  CompLedIndicator_UART_Transmit(UART_Service_UART_0_Id, &uart_tx_data[0], 4u);
  ret = CompLedIndicator_SPI_Get_Received(SPI_Service_SPI_0_Id, &rx_data[0], &data_length);
  
  uart_tx_data[4] = '0' + ret;
  CompLedIndicator_UART_Transmit(UART_Service_UART_0_Id, &uart_tx_data[4], 2u);

  if( (ret == RET_OK) && (data_length > 0u) )
  {
    for(i = 0; i < data_length; i++)
    {
      sum += rx_data[i];
    }
    avg = (uint8)(sum / (uint32)data_length);
    CompLedIndicator_PWM_Set_Pin(PWM_Service_PWM_PIN_0_Id, avg);
  }
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */
/* DO NOT REMOVE COMMENT - GEN END SECTION */