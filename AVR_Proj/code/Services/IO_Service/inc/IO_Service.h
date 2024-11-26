#ifndef IO_SERVICE_H
#define IO_SERVICE_H

#include "Types.h"
#include "GPIO.h"

typedef uint8 IO_Service_PinInputOutputType;
#define IO_Service_PIN_INPUT        0u
#define IO_Service_PIN_OUTPUT       1u
#define IO_Service_PIN_UNDEFINED    0xffu

/*  Pin_data  */
#define IO_Service_PIN_COUNT   1

#define IO_Service_PIN_0_ID            0
#define IO_Service_PIN_0_TYPE          IO_Service_PIN_OUTPUT

//#define GPIO_READ_PIN()

#define IO_Service_SET_PIN(pin_id)              GPIO_SET_PIN(pin_id)
#define IO_Service_UNSET_PIN(pin_id)            GPIO_UNSET_PIN(pin_id)
#define IO_Service_TOGGLE_PIN(pin_id)           GPIO_TOGGLE_PIN(pin_id) 

#endif