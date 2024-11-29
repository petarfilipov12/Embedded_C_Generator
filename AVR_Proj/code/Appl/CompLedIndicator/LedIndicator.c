#include "LedIndicator.h"

void CompLedIndicator_cyclic_100ms(void)
{
  uint8 pin_val = 0;

  if( (RET_OK == IO_Service_Read_Pin(IO_Service_PIN_1_ID, &pin_val)) && (IO_Service_PIN_LOW != pin_val) )
  {
    IO_Service_Set_Pin(IO_Service_PIN_0_ID, IO_Service_PIN_LOW);
  }
  else
  {
    IO_Service_Toggle_Pin(IO_Service_PIN_0_ID);
  }
  
}