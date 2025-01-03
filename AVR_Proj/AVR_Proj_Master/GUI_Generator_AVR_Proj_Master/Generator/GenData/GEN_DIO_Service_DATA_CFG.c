#include "GEN_DIO_Service_DATA_CFG.h"

DIO_Service_PinCfg_t DIO_Service_PinCfg_data[DIO_Service_DIO_Service_Pins_Count];

inline void DIO_Service_PinCfg_data_INIT_FUNC(void)
{
	DIO_Service_PinCfg_data[0].id = DIO_Service_DIO_PIN_0_Id;
	DIO_Service_PinCfg_data[0].pinState = DIO_Service_DIO_PIN_0_PinState;
	DIO_Service_PinCfg_data[0].pinType = DIO_Service_DIO_PIN_0_PinType;
	DIO_Service_PinCfg_data[0].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[1].id = DIO_Service_DIO_PIN_1_Id;
	DIO_Service_PinCfg_data[1].pinState = DIO_Service_DIO_PIN_1_PinState;
	DIO_Service_PinCfg_data[1].pinType = DIO_Service_DIO_PIN_1_PinType;
	DIO_Service_PinCfg_data[1].status = RET_NOT_OK;
}