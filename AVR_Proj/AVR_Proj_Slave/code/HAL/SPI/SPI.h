#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "Types.h"
#include "Queue.h"

extern Func_ReturnType SPI_MasterInit(uint8 spi_id);
extern Func_ReturnType SPI_Send(uint8 spi_id, uint8 tx_data, uint8 *rx_data, boolean *txrx_done);

extern Func_ReturnType SPI_SlaveInit(uint8 spi_id, Queue_t *rx_queue);

#endif