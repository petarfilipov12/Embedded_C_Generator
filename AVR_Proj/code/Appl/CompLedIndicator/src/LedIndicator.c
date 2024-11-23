#include "LedIndicator.h"

tDtcsLedIndicatorCfg LedIndicators[eLedIndicator_count] = {CompLedIndicator_LedIndicatorCfg_INIT};

static void CompLedIndicator_ToggleLedIndicator(uint8_t u8LedIndicatorIdP);

void CompLedIndicator_init(void)
{
  uint8_t u8IndexL = 0;

  for(u8IndexL = 0; u8IndexL < eLedIndicator_count; u8IndexL++)
  {
    SET_INDICATOR_AS_OUTPUT(LedIndicators[u8IndexL]);
    UNSET_INDICATOR(LedIndicators[u8IndexL]);
  }
}

void CompLedIndicator_cyclic_100ms(void)
{
  CompLedIndicator_ToggleLedIndicator(0);
}

static void CompLedIndicator_ToggleLedIndicator(uint8_t u8LedIndicatorIdP)
{
  if(u8LedIndicatorIdP < eLedIndicator_count)
  {
    TOGGLE_INDICATOR(LedIndicators[u8LedIndicatorIdP]);
  }

}