#include "GPT.h"

#include "GPT_Service.h"

GPT_sTimerDataCfg_t asGPTTimersCfg[GPT_TIMER_COUNT] = {GPT_TimerDataCfg_INIT};

Func_ReturnType GPT_Init_Timer(uint8 timer_id, uint8 timer_mode, uint8 compare_val, uint8 freq_prescalar)
{
    uint8 freq_prescalar_mask = 0u;

    *asGPTTimersCfg[timer_id].timer_mode_reg = 0u;
    *asGPTTimersCfg[timer_id].compare_val_reg = 0u;
    *asGPTTimersCfg[timer_id].freq_prescalar_reg = 0u;

    switch (timer_mode)
    {
    case GPT_Service_TIMER_MODE_NORMAL:
        // Set timer CTC
        *asGPTTimersCfg[timer_id].timer_mode_reg |= (1 << WGM01);
        break;
    case GPT_Service_TIMER_MODE_PWM:
        //Set timer PWM
        *asGPTTimersCfg[timer_id].timer_mode_reg |= (1 << WGM01) | (1 << WGM00);
        break;
    default:
        break;
    }

    *asGPTTimersCfg[timer_id].compare_val_reg = compare_val;

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

    *asGPTTimersCfg[timer_id].freq_prescalar_reg |= freq_prescalar_mask;

    return RET_OK;
}

Func_ReturnType GPT_Timer_Set_Compare_Value(uint8 timer_id, uint8 compare_val)
{
    *asGPTTimersCfg[timer_id].compare_val_reg = compare_val;

    return RET_OK;
}