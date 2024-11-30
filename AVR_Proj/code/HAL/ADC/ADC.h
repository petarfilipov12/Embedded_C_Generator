#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#include "Types.h"

#define ADC_SET_VOLTAGE_REF()       (ADMUX &= ~(1 << REFS1));   \
                                    (ADMUX |= (1 << REFS0))

#define ADC_SET_OUTPUT_RESOLUTION() (ADMUX |= (1 << ADLAR))

#define ADC_SET_CLOCK_PERSCALER()   (ADCSRA &= ~(1 << ADPS0));  \
                                    (ADCSRA |= (1 << ADPS1));   \
                                    (ADCSRA |= (1 << ADPS2))

#define ADC_ENABLE_ADC()            (ADCSRA |= (1 << ADEN))

#define ADC_START_MESUREMENT()      (ADCSRA |= (1 << ADSC))

#define ADC_IS_ADC_READY()   (!(ADCSRA & (1 << ADSC)))

#define ADC_SET_PIN_TO_MEASURE(pin_id)  (ADMUX &= 0xf0u);   \
                                        (ADMUX |= au8ADCPinsCfg[pin_id])

#define ADC_READ(value)      (*value = ADCH)

#define ADC_PIN_COUNT 1
#define ADC_PinDataCfg_INIT \
    PC0

extern Func_ReturnType ADC_Enable_ADC(void);
extern Func_ReturnType ADC_Start_Measurement(uint8 pin_id);

#endif