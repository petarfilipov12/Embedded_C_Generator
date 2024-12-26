#ifndef GEN_DATA_CFG_ADC_SERVICE_H
#define GEN_DATA_CFG_ADC_SERVICE_H

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

extern ADC_Service_AdcCfg_t ADC_Service_AdcHwCfg_data[ADC_Service_ADC_COUNT];

extern inline void ADC_Service_AdcHwCfg_data_INIT_FUNC(void);

#endif