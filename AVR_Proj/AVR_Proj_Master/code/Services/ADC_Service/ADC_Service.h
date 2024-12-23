#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_ADC_Service_CFG.h"

extern Func_ReturnType ADC_Service_Read_Pin(uint8 pin_id, uint8* value);

#endif