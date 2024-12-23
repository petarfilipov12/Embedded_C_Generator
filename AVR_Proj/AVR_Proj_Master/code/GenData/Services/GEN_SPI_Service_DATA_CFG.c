#include "GEN_SPI_Service_DATA_CFG.h"

SPI_Service_SpiMasterHwCfg_t SPI_Service_SpiMasterHwCfg_data[SPI_Service_SPI_MASTER_HW_COUNT] = {SPI_Service_SpiMasterHwCfg_data_INIT};

uint8 SPI_Service_SPI_SLAVE_SPI_1_RxBuffer[SPI_Service_SPI_SLAVE_SPI_1_BUFFER_SIZE];

SPI_Service_SpiSlaveHwCfg_t SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_HW_COUNT];

inline void SPI_Service_SpiSlaveHwCfg_data_INIT_FUNC(void)
{
    SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_SPI_1_ID].pu8SpiRxBuffer = &SPI_Service_SPI_SLAVE_SPI_1_RxBuffer[0];
    SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_SPI_1_ID].u8SpiRxBufferSize = SPI_Service_SPI_SLAVE_SPI_1_BUFFER_SIZE;
    SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_SPI_1_ID].status = RET_NOT_OK;
}