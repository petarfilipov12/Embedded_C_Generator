#ifndef GEN_CFG_DIO_SERVICE_H
#define GEN_CFG_DIO_SERVICE_H

#define DIO_Service_PIN_0_ID             0u
#define DIO_Service_PIN_0_INIT_STATE     DIO_Service_PIN_LOW
#define DIO_Service_PIN_0_INIT_TYPE      DIO_Service_PIN_OUTPUT

#define DIO_Service_PIN_1_ID             1u
#define DIO_Service_PIN_1_INIT_STATE     DIO_Service_PIN_LOW
#define DIO_Service_PIN_1_INIT_TYPE      DIO_Service_PIN_INPUT

#define DIO_Service_PIN_COUNT            2u

#define DIO_Service_Pin_data_INIT \
/* PIN_0 */ {DIO_Service_PIN_0_INIT_TYPE, DIO_Service_PIN_0_INIT_STATE, RET_NOT_OK}, \
/* PIN_1 */ {DIO_Service_PIN_1_INIT_TYPE, DIO_Service_PIN_1_INIT_STATE, RET_NOT_OK}

#endif