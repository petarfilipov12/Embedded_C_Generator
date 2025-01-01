#ifndef SPI_SERVICE_H
#define SPI_SERVICE_H

#include "Types.h"
#include "GEN_SPI_Service_CFG.h"

typedef struct{
    Queue_t spiRxQueue;
    uint8* spiRxBuffer;
    uint8 spiRxBufferSize;
    uint8 id;
    uint8 spiMode;
    Func_ReturnType status;
}SPI_Service_SpiCfg_t;

#endif