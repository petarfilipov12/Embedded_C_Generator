#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_ADC_Service_CFG.h"

typedef struct{
    Queue_t sAdcQueue;
    uint8* pu8AdcBuffer;
    uint8 u8AdcBufferSize;
    uint8 current_pin_id;
    Func_ReturnType status;
}ADC_Service_AdcCfg_t;

extern Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value);

#endif