#include "LedIndicator.h"

void CompLedIndicator_cyclic_100ms(void)
{
  IO_Service_TOGGLE_PIN(IO_Service_PIN_0_ID);
}