#ifndef GEN_DATA_CFG_SPI_SERVICE_H
#define GEN_DATA_CFG_SPI_SERVICE_H

#include "Types.h"
#include "Queue.h"
#include "GEN_SPI_Service_CFG.h"

typedef struct{
    Func_ReturnType status;
}SPI_Service_SpiMasterHwCfg_t;

#define SPI_Service_SpiMasterHwCfg_data_INIT    \
{RET_NOT_OK}, //SPI_MASTER_SPI_0_ID

extern SPI_Service_SpiMasterHwCfg_t SPI_Service_SpiMasterHwCfg_data[SPI_Service_SPI_MASTER_HW_COUNT];

typedef struct{
    Queue_t sSpiRxQueue;
    uint8* pu8SpiRxBuffer;
    uint8 u8SpiRxBufferSize;
    Func_ReturnType status;
}SPI_Service_SpiSlaveHwCfg_t;

extern SPI_Service_SpiSlaveHwCfg_t SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_HW_COUNT];

extern inline void SPI_Service_SpiSlaveHwCfg_data_INIT_FUNC(void);

#endif