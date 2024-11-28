#include "LedIndicator.h"

void CompLedIndicator_cyclic_100ms(void)
{
  if(IO_Service_READ_PIN(IO_Service_PIN_1_ID) != IO_Service_PIN_LOW)
  {
    IO_Service_SET_PIN_LOW(IO_Service_PIN_0_ID);
  }
  else
  {
    IO_Service_TOGGLE_PIN(IO_Service_PIN_0_ID);
  }
}