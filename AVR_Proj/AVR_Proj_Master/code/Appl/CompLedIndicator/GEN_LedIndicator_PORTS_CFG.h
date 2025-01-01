#ifndef GEN_LEDINDICATOR_PORTS_CFG_H
#define GEN_LEDINDICATOR_PORTS_CFG_H

#include "Types.h"

/*Server Ports*/

/*Client Ports*/
#include "GEN_DIO_Service_PORTS_CFG.h"
#define LedIndicator_Set_Pin    DIO_Service_Set_Pin
#define LedIndicator_Read_Pin    DIO_Service_Read_Pin
#define LedIndicator_Write_Pin    DIO_Service_Write_Pin
#define LedIndicator_Toggle_Pin    DIO_Service_Toggle_Pin

#endif