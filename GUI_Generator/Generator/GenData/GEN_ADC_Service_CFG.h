#ifndef GEN_ADC_SERVICE_CFG_H
#define GEN_ADC_SERVICE_CFG_H

#include "Types.h"

#define ADC_Service_ADC_Service_ADCs_Count 1

#define ADC_Service_ADC_0_AdcBufferSize 10
#define ADC_Service_ADC_0_Id 0


#define ADC_Service_ADC_Service_Pins_Count 1

#define ADC_Service_ADC_PIN_0_AdcRef ADC_0
#define ADC_Service_ADC_PIN_0_Id 0


#define ADC_Service_Data_Init \
/* ADC_PIN_0 */{ADC_Service_ADC_PIN_0_AdcRef, ADC_Service_ADC_PIN_0_Id, RET_NOT_OK}

#endif