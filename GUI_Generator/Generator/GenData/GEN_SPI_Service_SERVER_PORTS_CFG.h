#ifndef GEN_SPI_SERVICE_SERVER_PORTS_CFG_H
#define GEN_SPI_SERVICE_SERVER_PORTS_CFG_H

extern Func_ReturnType SPI_Service_Transmit(uint8 spi_id, uint8* tx_data, uint8* rx_data, uint8 data_length);
extern Func_ReturnType SPI_Service_GetReceived(uint8 spi_id, uint8* rx_data, uint8* data_length);

#endif