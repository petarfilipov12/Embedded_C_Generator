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

  uint8 spi_tx_data_1[5] = {1, 1, 1, 1, 1};
  uint8 spi_tx_data_0[5] = {0};
  uint8 spi_rx_data[5] = {0};

  Func_ReturnType ret = RET_OK;

  if( (RET_OK == IO_Service_Read_Pin(IO_Service_PIN_1_ID, &pin_val)) && (IO_Service_PIN_HIGH != pin_val) )
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
    UART_Service_Transmit(UART_Service_UART_0_ID, &uart_tx_data[0], (uint8)(sizeof(uart_tx_data)/sizeof(uart_tx_data[0])));

    SPI_Service_Transmit(SPI_Service_SPI_MASTER_SPI_0_ID, &spi_tx_data_1[0], &spi_rx_data[0], 5u);
  }
  else
  {
    SPI_Service_Transmit(SPI_Service_SPI_MASTER_SPI_0_ID, &spi_tx_data_0[0], &spi_rx_data[0], 5u);

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