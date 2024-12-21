#ifndef PWM_H
#define PWM_H

#include "Types.h"
#include <avr/io.h>

typedef struct{
    volatile uint8_t* ddr;
    volatile uint8_t* timer_pin_reg;
    uint8_t timer_pin_set_mask;
    uint8_t pin;
}PWM_sPinDataCfg_t;

#define PWM_PIN_COUNT  1

#define PWM_PinDataCfg_INIT                \
/*     ddr, timer_pin_reg, pin    */      \
    {&DDRD, &TCCR0A, 0x80u, PD6}

extern PWM_sPinDataCfg_t asPWMPinsCfg[PWM_PIN_COUNT];


extern Func_ReturnType PWM_Init_Pin(uint8 pin_id);

#endif