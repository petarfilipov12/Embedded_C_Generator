#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

#include "Types.h"

typedef uint8 GPIO_PinInputOutputType;
#define GPIO_PIN_INPUT      0
#define GPIO_PIN_OUTPUT     1

typedef uint8 GPIO_PinStateType;
#define GPIO_PIN_LOW        0
#define GPIO_PIN_HIGH       1

#define GPIO_PIN_UNDEFINED  0xffu

typedef struct{
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* read_reg;
    uint8_t pin;
}GPIO_sPinDataCfg_t;

#define GPIO_PIN_COUNT  2

#define GPIO_PinDataCfg_INIT                \
/*     ddr, port, ,read_reg, pin    */      \
    {&DDRB, &PORTB, &PINB, PB0},            \
    {&DDRD, &PORTD, &PIND, PD4}

extern GPIO_sPinDataCfg_t asGPIOPinsCfg[GPIO_PIN_COUNT];

#define GPIO_SET_PIN_AS_INPUT(index)        (*asGPIOPinsCfg[index].ddr &= ~(1 << asGPIOPinsCfg[index].pin))
#define GPIO_SET_PIN_PULL_UP(index)         (*asGPIOPinsCfg[index].port |= (1 << asGPIOPinsCfg[index].pin))
#define GPIO_SET_PIN_PULL_DOWN(index)       (*asGPIOPinsCfg[index].port &= ~ (1 << asGPIOPinsCfg[index].pin))
#define GPIO_READ_PIN(index)                ((*asGPIOPinsCfg[index].read_reg & (1 << asGPIOPinsCfg[index].pin)) >> asGPIOPinsCfg[index].pin)

#define GPIO_SET_PIN_AS_OUTPUT(index)       (*asGPIOPinsCfg[index].ddr |= (1 << asGPIOPinsCfg[index].pin))
#define GPIO_SET_PIN_HIGH(index)            (*asGPIOPinsCfg[index].port |= (1 << asGPIOPinsCfg[index].pin))
#define GPIO_SET_PIN_LOW(index)             (*asGPIOPinsCfg[index].port &= ~(1 << asGPIOPinsCfg[index].pin))
#define GPIO_TOGGLE_PIN(index)              (*asGPIOPinsCfg[index].port ^= (1 << asGPIOPinsCfg[index].pin))

extern Func_ReturnType GPIO_Init_PIN(uint8 pin_id, GPIO_PinInputOutputType pin_type);

#endif