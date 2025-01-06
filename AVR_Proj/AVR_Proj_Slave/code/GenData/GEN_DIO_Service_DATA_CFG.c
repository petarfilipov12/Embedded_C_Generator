#include "GEN_DIO_Service_DATA_CFG.h"

DIO_Service_PinCfg_t DIO_Service_PinCfg_data[DIO_Service_DIO_Service_Pins_Count];

inline void DIO_Service_PinCfg_data_INIT_FUNC(void)
{
	DIO_Service_PinCfg_data[0].id = DIO_Service_DIO_LCD_D4_Id;
	DIO_Service_PinCfg_data[0].pinState = DIO_Service_DIO_LCD_D4_PinState;
	DIO_Service_PinCfg_data[0].pinType = DIO_Service_DIO_LCD_D4_PinType;
	DIO_Service_PinCfg_data[0].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[1].id = DIO_Service_DIO_LCD_D5_Id;
	DIO_Service_PinCfg_data[1].pinState = DIO_Service_DIO_LCD_D5_PinState;
	DIO_Service_PinCfg_data[1].pinType = DIO_Service_DIO_LCD_D5_PinType;
	DIO_Service_PinCfg_data[1].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[2].id = DIO_Service_DIO_LCD_D6_Id;
	DIO_Service_PinCfg_data[2].pinState = DIO_Service_DIO_LCD_D6_PinState;
	DIO_Service_PinCfg_data[2].pinType = DIO_Service_DIO_LCD_D6_PinType;
	DIO_Service_PinCfg_data[2].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[3].id = DIO_Service_DIO_LCD_D7_Id;
	DIO_Service_PinCfg_data[3].pinState = DIO_Service_DIO_LCD_D7_PinState;
	DIO_Service_PinCfg_data[3].pinType = DIO_Service_DIO_LCD_D7_PinType;
	DIO_Service_PinCfg_data[3].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[4].id = DIO_Service_DIO_LCD_E_Id;
	DIO_Service_PinCfg_data[4].pinState = DIO_Service_DIO_LCD_E_PinState;
	DIO_Service_PinCfg_data[4].pinType = DIO_Service_DIO_LCD_E_PinType;
	DIO_Service_PinCfg_data[4].status = RET_NOT_OK;

	DIO_Service_PinCfg_data[5].id = DIO_Service_DIO_LCD_RS_Id;
	DIO_Service_PinCfg_data[5].pinState = DIO_Service_DIO_LCD_RS_PinState;
	DIO_Service_PinCfg_data[5].pinType = DIO_Service_DIO_LCD_RS_PinType;
	DIO_Service_PinCfg_data[5].status = RET_NOT_OK;
}