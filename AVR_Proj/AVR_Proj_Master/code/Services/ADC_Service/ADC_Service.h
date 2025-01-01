#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_ADC_Service_CFG.h"

typedef struct{
    Queue_t AdcQueue;
    uint8* AdcBuffer;
    uint8 AdcBufferSize;
    uint8 id;
    uint8 current_pin_id;
    Func_ReturnType status;
}ADC_Service_AdcCfg_t;

typedef struct{
    uint8 adcref;
    uint8 id;
    uint8 last_value;
    Func_ReturnType status;
}ADC_Service_PinCfg_t;

#endif