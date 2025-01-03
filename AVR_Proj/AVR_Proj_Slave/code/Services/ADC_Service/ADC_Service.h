#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_ADC_Service_CFG.h"

typedef struct{
    Queue_t adcQueue;
    uint8* adcBuffer;
    uint8 adcBufferSize;
    uint8 id;
    uint8 currentPinId;
    Func_ReturnType status;
}ADC_Service_AdcCfg_t;

typedef struct{
    uint8 adcRef;
    uint8 id;
    uint8 lastValue;
    Func_ReturnType status;
}ADC_Service_PinCfg_t;

#endif