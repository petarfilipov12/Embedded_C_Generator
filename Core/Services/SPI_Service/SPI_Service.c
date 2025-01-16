#include "SPI_Service.h"
#include "GEN_SPI_Service_DATA_CFG.h"
#include "Queue.h"
#include "SPI.h"

boolean txrx_done = TRUE;

void SPI_Service_Init(void)
{
#if SPI_Service_SPI_Service_SPIs_Count > 0
    uint8 spi_id = 0;

    SPI_Service_SpiHwCfg_data_INIT_FUNC();

    for(spi_id=0; spi_id<SPI_Service_SPI_Service_SPIs_Count; spi_id++)
    {
        Queue_Init(
            &SPI_Service_SpiHwCfg_data[spi_id].spiRxQueue,
            &SPI_Service_SpiHwCfg_data[spi_id].spiRxBuffer[0],
            SPI_Service_SpiHwCfg_data[spi_id].spiRxBufferSize
        );

        if(SPI_Service_SpiHwCfg_data[spi_id].spiMode == SPI_MODE_MASTER)
        {
            SPI_Service_SpiHwCfg_data[spi_id].status = SPI_MasterInit(spi_id);
        }
        else if(SPI_Service_SpiHwCfg_data[spi_id].spiMode == SPI_MODE_SLAVE)
        {
            SPI_Service_SpiHwCfg_data[spi_id].status = SPI_SlaveInit(spi_id, &SPI_Service_SpiHwCfg_data[spi_id].spiRxQueue);
        }
        else
        {
            //Should not reach here - Wrong SPI mode
        }
        
    }
#endif
}

Func_ReturnType SPI_Service_Transmit(uint8 spi_id, uint8 *tx_data, uint8 *rx_data, uint8 data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if SPI_Service_SPI_Service_SPIs_Count > 0
    uint8 i = 0;

    if(SPI_Service_SpiHwCfg_data[spi_id].spiMode == SPI_MODE_MASTER)
    {
        ret = SPI_Service_SpiHwCfg_data[spi_id].status;

        if(ret == RET_OK)
        {
            SPI_Service_SpiHwCfg_data[spi_id].status = RET_BUSY;

            i = 0;
            while(i < data_length)
            {
                if(txrx_done != FALSE)
                {
                    SPI_Send(spi_id, tx_data[i], &rx_data[i], &txrx_done);
                    i++;
                }
            }

            //while(txrx_done == FALSE);

            SPI_Service_SpiHwCfg_data[spi_id].status = RET_OK;
        }
    }
#endif

    return ret;
}

Func_ReturnType SPI_Service_GetReceived(uint8 spi_id, uint8 *rx_data, uint8 *data_length)
{
    Func_ReturnType ret = RET_NOT_OK;

#if SPI_Service_SPI_Service_SPIs_Count > 0
    uint8 i = 0; 

    if(SPI_Service_SpiHwCfg_data[spi_id].spiMode == SPI_MODE_SLAVE)
    {
        ret = Queue_Length(&SPI_Service_SpiHwCfg_data[spi_id].spiRxQueue, &data_length[0]);

        if(RET_OK == ret)
        {
            for(i = 0; i < *data_length; i++)
            {
                Queue_Pop(&SPI_Service_SpiHwCfg_data[spi_id].spiRxQueue, &rx_data[i]);
            }
            //memcpy(&rx_data[0], &SPI_Service_SpiHwCfg_data[spi_id].spiRxBuffer[0], *data_length);
            ret = RET_OK;
        }
    }
#endif
    
    return ret;
}