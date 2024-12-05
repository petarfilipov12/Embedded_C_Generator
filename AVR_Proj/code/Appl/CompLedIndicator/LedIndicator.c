#include "LedIndicator.h"

void CompLedIndicator_Init(void)
{
  uint8 uart_data[4] = {'I', 'N', 'I', 'T'};

  UART_Service_Transmit(UART_Service_UART_0_ID, &uart_data[0], (uint8)(sizeof(uart_data)/sizeof(uart_data[0])));
}

void CompLedIndicator_cyclic_100ms(void)
{
  uint8 pin_val = 0;
  uint8 uart_data[6] = {84, 79, 71, 71, 76, 69, 10};

  if( (RET_OK == IO_Service_Read_Pin(IO_Service_PIN_1_ID, &pin_val)) && (IO_Service_PIN_HIGH != pin_val) )
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
    UART_Service_Transmit(UART_Service_UART_0_ID, &uart_data[0], (uint8)(sizeof(uart_data)/sizeof(uart_data[0])));
  }
  else
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
    IO_Service_Set_Pin(IO_Service_PIN_0_ID, IO_Service_PIN_LOW);
  }
  
}