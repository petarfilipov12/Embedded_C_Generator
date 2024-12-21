#include "SPI.h"

#define SPI_MODE_MASTER 0u
#define SPI_MODE_SLAVE 1u
#define SPI_MODE_INVALID 0xffu

//slave variables
Queue_t *psRxQueue = NULL;

//Master variables
volatile uint8 *pu8TransmitRxData = NULL;
volatile boolean *pbTxRxDone = NULL;
static volatile boolean spi_busy = TRUE;

static uint8 spi_mode = SPI_MODE_INVALID;

static void SPI_ActivateSlave(void);
static void SPI_DeactivateSlave(void);

static void SPI_ActivateSlave(void)
{
    PORTB &= ~(1 << PB2);
}

static void SPI_DeactivateSlave(void)
{
    PORTB |= (1 << PB2);
}

Func_ReturnType SPI_MasterInit(uint8 spi_id)
{
    Func_ReturnType ret = RET_NOT_OK;

    if(spi_mode == SPI_MODE_INVALID)
    {
        spi_mode = SPI_MODE_MASTER;

        DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
        SPI_DeactivateSlave();

        SPCR = (1 << SPE) | (1 << MSTR);

        SPCR |= (1 << SPIE);
        SPCR |= (1 << SPR1); //clock devider /64 -> 8000000 / 64 = 125000 Hz

        SPI_ActivateSlave();

        spi_busy = FALSE;

        ret = RET_OK;
    }
    

    return ret;
}

Func_ReturnType SPI_SlaveInit(uint8 spi_id, Queue_t *rx_queue)
{
    Func_ReturnType ret = RET_NOT_OK;

    if(spi_mode == SPI_MODE_INVALID)
    {
        spi_mode = SPI_MODE_SLAVE;

        psRxQueue = rx_queue;

        DDRB |= (1 << DDB4);

        SPCR = (1 << SPE);

        SPCR |= (1 << SPIE);
        SPCR |= (1 << SPR1); //clock devider /64 -> 8000000 / 64 = 125000 Hz

        ret = RET_OK;
    }

    return ret;
}

Func_ReturnType SPI_Send(uint8 spi_id, uint8 tx_data, uint8 *rx_data, boolean *txrx_done)
{
    Func_ReturnType ret = RET_BUSY;

    if(spi_busy == FALSE)
    {
        pu8TransmitRxData = rx_data;
        pbTxRxDone = txrx_done;

        *pbTxRxDone = FALSE;

        SPDR = tx_data;

        ret = RET_OK;
    }

    return ret;
}

static inline void SPI_HandleMasterInterrupt(void)
{
    if(SPSR & (1 << WCOL))
    {
        *pu8TransmitRxData = SPDR;
        *pu8TransmitRxData = 0;
    }
    else
    {
        *pu8TransmitRxData = SPDR;
    }

    *pbTxRxDone = TRUE;
    spi_busy = FALSE;
}

static inline void SPI_HandleSlaveInterrupt(void)
{
    Queue_Put(psRxQueue, SPDR);
}

ISR(SPI_STC_vect)
{
    if(spi_mode == SPI_MODE_MASTER)
    {
        SPI_HandleMasterInterrupt();
    }
    else if(spi_mode == SPI_MODE_SLAVE)
    {
        SPI_HandleSlaveInterrupt();
    }
    else
    {
        //Nothing to do
    }
}