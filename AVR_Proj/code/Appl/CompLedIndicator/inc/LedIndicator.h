#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include "Types.h"
#include <avr/io.h>

typedef struct{
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    uint8_t pin;
    uint8_t id;
}tDtcsLedIndicatorCfg;

typedef enum{
    eLedIndicator_indicator_1,
    eLedIndicator_count
}eLedInicator;

#define CompLedIndicator_LedIndicatorCfg_INIT   \
/*      ddr, port, pin, id, state       */      \
    {&DDRB, &PORTB, PB0, 0}

extern tDtcsLedIndicatorCfg LedIndicators[eLedIndicator_count];

#define SET_INDICATOR_AS_OUTPUT(indicator_elem) (*indicator_elem.ddr |= (1 << indicator_elem.pin))

#define SET_INDICATOR(indicator_elem)    (*indicator_elem.port |= (1 << indicator_elem.pin))
#define UNSET_INDICATOR(indicator_elem)  (*indicator_elem.port &= ~(1 << indicator_elem.pin))
#define TOGGLE_INDICATOR(indicator_elem) (*indicator_elem.port ^= (1 << indicator_elem.pin))

extern void CompLedIndicator_init(void);
extern void CompLedIndicator_cyclic_100ms(void);


#endif