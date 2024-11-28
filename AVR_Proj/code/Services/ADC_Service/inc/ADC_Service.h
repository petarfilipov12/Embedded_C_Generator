#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "Types.h"
#include "ADC.h"

#define ADC_PIN_SATE_IDLE                           0u
#define ADC_PIN_SATE_WAITING_TO_START_MEASUREMENT   1u
#define ADC_PIN_SATE_MEASURING                      2u
#define ADC_PIN_SATE_MEASUREMENT_READY              3u


typedef struct{
    uint8 last_val;
    uint8 state;
}ADC_sPinDataCfg_t;

#define ADC_Service_PIN_1_ID             0
#define ADC_Service_PIN_COUNT            1

#define ADC_PinDataCfg_INIT                 \
/*     last_val, state, ,read_reg, pin    */\
    {0u, ADC_PIN_SATE_IDLE}

#endif