#ifndef SPI_SERVICE_H
#define SPI_SERVICE_H

#include "Types.h"
#include "GEN_SPI_Service_CFG.h"

extern Func_ReturnType SPI_Service_Transmit(uint8 spi_id, uint8 *tx_data, uint8 *rx_data, uint8 data_length);
extern Func_ReturnType SPI_Service_GetReceived(uint8 spi_id, uint8 *rx_data, uint8 *data_length);

#endif