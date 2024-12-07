#include "LedIndicator.h"

void CompLedIndicator_Init(void)
{
  uint8 uart_tx_data[5] = {'I', 'N', 'I', 'T', '\n'};

  UART_Service_Transmit(UART_Service_UART_0_ID, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));
}

void CompLedIndicator_cyclic_100ms(void)
{
  uint8 pin_val = 0;
  uint8 uart_tx_data[7] = {'T', 'O', 'G', 'G', 'L', 'E', '\n'};
  uint8 uart_rx_data[UART_Service_UART_RX_BUFFER_SIZE];
  uint8 uart_rx_data_length;
  uint8 temp = 0;
  Func_ReturnType ret = RET_OK;

  if( (RET_OK == IO_Service_Read_Pin(IO_Service_PIN_1_ID, &pin_val)) && (IO_Service_PIN_HIGH != pin_val) )
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
    UART_Service_Transmit(UART_Service_UART_0_ID, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));
  }
  else
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
    IO_Service_Set_Pin(IO_Service_PIN_0_ID, IO_Service_PIN_LOW);
  }

  ret = UART_Service_Read(UART_Service_UART_0_ID, &uart_rx_data[0], &uart_rx_data_length);
  if(RET_OK == ret)
  {
    if(uart_rx_data_length > 0)
    {
      uint8 i = 0;

      for (i=0; i<uart_rx_data_length; i++)
      {
        UART_Service_Transmit(UART_Service_UART_0_ID, &uart_rx_data[i], 1u);
      }
      
    }
  }
  
}