#ifndef GEN_SPI_SERVICE_DATA_CFG_H
#define GEN_SPI_SERVICE_DATA_CFG_H

#include "Types.h"
#include "Queue.h"
#include "GEN_SPI_Service_CFG.h"
#include "SPI_Service.h"

extern SPI_Service_SpiCfg_t SPI_Service_SpiHwCfg_data[SPI_Service_SPI_Service_SPIs_Count];

extern inline void SPI_Service_SpiHwCfg_data_INIT_FUNC(void);

#endif