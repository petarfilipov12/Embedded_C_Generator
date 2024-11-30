#include "PWM.h"

PWM_sTimerDataCfg_t asPWMTimersCfg[PWM_TIMER_COUNT] = {PWM_TimerDataCfg_INIT};
PWM_sPinDataCfg_t asPWMPinsCfg[PWM_PIN_COUNT] = {PWM_PinDataCfg_INIT};

Func_ReturnType PWM_Init_Timer(uint8 timer_id, uint8 freq_prescalar)
{
    uint8 freq_prescalar_mask = 0u;

    *asPWMTimersCfg[timer_id].pwm_mode_reg |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    *asPWMTimersCfg[timer_id].pwm_mode_reg &= ~(1 << COM0A0);
    *asPWMTimersCfg[timer_id].freq_prescalar_reg &= 0xf8u;

    switch (freq_prescalar)
    {
    case 1u:
        freq_prescalar_mask = 0x01u;
        break;
    case 8u:
        freq_prescalar_mask = 0x02u;
        break;
    case 64u:
        freq_prescalar_mask = 0x03u;
        break;
    case 256u:
        freq_prescalar_mask = 0x04u;
        break;
    case 1024u:
        freq_prescalar_mask = 0x05u;
        break;
    default:
        break;
    }

    *asPWMTimersCfg[timer_id].freq_prescalar_reg |= freq_prescalar_mask;

    return RET_OK;
}

Func_ReturnType PWM_Init_Pin(uint8 pin_id)
{
    *asPWMPinsCfg[pin_id].ddr |= (1 << asPWMPinsCfg[pin_id].pin);

    return RET_OK;
}

Func_ReturnType PWM_Set_Pin(uint8 pin_id, uint8 duty_cycle)
{
    *asPWMPinsCfg[pin_id].dute_cycle_reg = duty_cycle;

    return RET_OK;
}