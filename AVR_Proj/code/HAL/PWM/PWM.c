#include "PWM.h"
#include "GPT.h"

PWM_sPinDataCfg_t asPWMPinsCfg[PWM_PIN_COUNT] = {PWM_PinDataCfg_INIT};

Func_ReturnType PWM_Init_Pin(uint8 pin_id)
{
    *asPWMPinsCfg[pin_id].ddr |= (1 << asPWMPinsCfg[pin_id].pin);

    *asPWMPinsCfg[pin_id].timer_pin_reg |= asPWMPinsCfg[pin_id].timer_pin_set_mask;

    return RET_OK;
}