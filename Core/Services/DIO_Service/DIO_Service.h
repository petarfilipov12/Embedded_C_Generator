#ifndef DIO_SERVICE_H
#define DIO_SERVICE_H

#include "Types.h"
#include "GEN_DIO_Service_CFG.h"

typedef struct{
    uint8 id;
    uint8 pinState;
    uint8 pinType;
    Func_ReturnType status;
}DIO_Service_PinCfg_t;

#endif