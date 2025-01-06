#ifndef GEN_LCD_DRIVER_CLIENT_PORTS_CFG_H
#define GEN_LCD_DRIVER_CLIENT_PORTS_CFG_H

#include "GEN_DIO_Service_SERVER_PORTS_CFG.h"
#include "GEN_DIO_Service_CFG.h"
#include "GEN_PWM_Service_SERVER_PORTS_CFG.h"
#include "GEN_PWM_Service_CFG.h"

#define LCD_Driver_DIO_Set_Pin	DIO_Service_Set_Pin
#define LCD_Driver_DIO_Write_Pin	DIO_Service_Write_Pin
#define LCD_Driver_PWM_Set_Pin	PWM_Service_Set_Pin

#endif