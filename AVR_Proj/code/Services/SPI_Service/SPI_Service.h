#ifndef SPI_SERVICE_H
#define SPI_SERVICE_H

#include "SPI.h"

#define SPI_Service_MODE_MASTER 0u
#define SPI_Service_MODE_SLAVE 1u

#define SPI_Service_SPI_RX_BUFFER_SIZE 20u

#define SPI_Service_SPI_MASTER_SPI_0_ID        0u
#define SPI_Service_SPI_MASTER_HW_COUNT       1u

//#define SPI_Service_SPI_SLAVE_SPI_1_ID        0u
#define SPI_Service_SPI_SLAVE_HW_COUNT       0u

extern Func_ReturnType SPI_Service_Transmit(uint8 spi_id, uint8 *tx_data, uint8 *rx_data, uint8 data_length);

#endif