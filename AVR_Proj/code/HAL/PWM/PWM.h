#ifndef PWM_H
#define PWM_H

#include "Types.h"
#include <avr/io.h>

typedef struct{
    volatile uint8_t* pwm_mode_reg;
    volatile uint8_t* freq_prescalar_reg;
}PWM_sTimerDataCfg_t;

#define PWM_TIMER_COUNT  1

#define PWM_TimerDataCfg_INIT                \
/*     pwm_mode_reg, freq_prescalar_reg    */      \
    {&TCCR0A, &TCCR0B}

extern PWM_sTimerDataCfg_t asPWMTimersCfg[PWM_TIMER_COUNT];

typedef struct{
    volatile uint8_t* ddr;
    volatile uint8_t* dute_cycle_reg;
    uint8_t pin;
}PWM_sPinDataCfg_t;

#define PWM_PIN_COUNT  1

#define PWM_PinDataCfg_INIT                \
/*     ddr, dute_cycle_reg, pin    */      \
    {&DDRD, &OCR0A, PD6}

extern PWM_sPinDataCfg_t asPWMPinsCfg[PWM_PIN_COUNT];


extern Func_ReturnType PWM_Init_Timer(uint8 timer_id, uint8 freq_prescalar);
extern Func_ReturnType PWM_Init_Pin(uint8 pin_id);
extern Func_ReturnType PWM_Set_Pin(uint8 pin_id, uint8 duty_cycle);

#endif