#include "SPI_Service.h"
#include "Queue.h"

typedef struct{
    Func_ReturnType status;
}SPI_Service_SpiMasterHwCfg_t;

SPI_Service_SpiMasterHwCfg_t SPI_Service_SpiMasterHwCfg_data[SPI_Service_SPI_MASTER_HW_COUNT];

#if SPI_Service_SPI_SLAVE_HW_COUNT > 0u
typedef struct{
    Queue_t sSpiRxQueue;
    uint8 au8SpiRxBuffer[SPI_Service_SPI_RX_BUFFER_SIZE];
    Func_ReturnType status;
}SPI_Service_SpiSlaveHwCfg_t;

SPI_Service_SpiSlaveHwCfg_t SPI_Service_SpiSlaveHwCfg_data[SPI_Service_SPI_SLAVE_HW_COUNT];
#endif

void SPI_Service_Init(void)
{
    uint8 spi_id = 0;

    for(spi_id=0; spi_id<SPI_Service_SPI_MASTER_HW_COUNT; spi_id++)
    {
        SPI_Service_SpiMasterHwCfg_data[spi_id].status = SPI_MasterInit(spi_id);
    }

#if SPI_Service_SPI_SLAVE_HW_COUNT > 0u
    for(spi_id=0; spi_id<SPI_Service_SPI_SLAVE_HW_COUNT; spi_id++)
    {
        Queue_Init(
            &SPI_Service_SpiSlaveHwCfg_data[spi_id].sSpiRxQueue,
            &SPI_Service_SpiSlaveHwCfg_data[spi_id].au8SpiRxBuffer[0],
            SPI_Service_SPI_RX_BUFFER_SIZE
        );

        SPI_Service_SpiSlaveHwCfg_data[spi_id].status = SPI_SlaveInit(spi_id, &SPI_Service_SpiSlaveHwCfg_data[spi_id].sSpiRxQueue);
    }
#endif
}

Func_ReturnType SPI_Service_Transmit(uint8 spi_id, uint8 *tx_data, uint8 *rx_data, uint8 data_length)
{
    uint8 i = 0;
    boolean txrx_done = TRUE;
    Func_ReturnType ret = SPI_Service_SpiMasterHwCfg_data[spi_id].status;

    if(ret == RET_OK)
    {
        SPI_Service_SpiMasterHwCfg_data[spi_id].status = RET_BUSY;

        while(i < data_length)
        {
            if(txrx_done != FALSE)
            {
                SPI_Send(spi_id, tx_data[i], &rx_data[i], &txrx_done);
                i++;
            }
        }

        //while(txrx_done == FALSE);

        SPI_Service_SpiMasterHwCfg_data[spi_id].status = RET_OK;
    }

    return ret;
}

Func_ReturnType SPI_Service_GetReceived(uint8 spi_id, uint8 *rx_data, uint8 *data_length)
{
    Func_ReturnType ret = RET_QUEUE_EMPTY;

    if(RET_OK == Queue_Length(&SPI_Service_SpiSlaveHwCfg_data[spi_id].sSpiRxQueue, &data_length[0]))
    {
        memcpy(&rx_data[0], &SPI_Service_SpiSlaveHwCfg_data[spi_id].au8SpiRxBuffer[0], *data_length);

        ret = RET_OK;
    }
    
    return ret;
}