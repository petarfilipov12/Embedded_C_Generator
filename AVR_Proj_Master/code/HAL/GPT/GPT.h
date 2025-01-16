#ifndef GPT_H
#define GPT_H

#include "Types.h"
#include <avr/io.h>

#include "PWM.h"

typedef struct{
    volatile uint8_t* timer_mode_reg;
    volatile uint8_t* compare_val_reg;
    volatile uint8_t* freq_prescalar_reg;
}GPT_sTimerDataCfg_t;

#define GPT_TIMER_COUNT  1

#define GPT_TimerDataCfg_INIT                \
/*     GPT_mode_reg, compare_val_reg, freq_prescalar_reg    */      \
    {&TCCR0A, &OCR0A, &TCCR0B}

extern GPT_sTimerDataCfg_t asGPTTimersCfg[GPT_TIMER_COUNT];

extern Func_ReturnType GPT_Init_Timer(uint8 timer_id, uint8 timer_mode, uint8 compare_val, uint8 freq_prescalar);
Func_ReturnType GPT_Timer_Set_Compare_Value(uint8 timer_id, uint8 compare_val);

#endif