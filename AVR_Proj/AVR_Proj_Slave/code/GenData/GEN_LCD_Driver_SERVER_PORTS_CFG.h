#ifndef GEN_LCD_DRIVER_SERVER_PORTS_CFG_H
#define GEN_LCD_DRIVER_SERVER_PORTS_CFG_H

#include "Types.h"
#include "Queue.h"

extern uint8 LCD_Driver_LCD_Status;
extern Func_ReturnType LCD_Driver_LCD_Begin();
extern Func_ReturnType LCD_Driver_LCD_Clear();
extern Func_ReturnType LCD_Driver_LCD_SetCursor(uint8 line, uint8 pos);
extern Func_ReturnType LCD_Driver_LCD_WriteString(uint8* data, uint8 data_length);
extern Func_ReturnType LCD_Driver_LCD_WriteNumber(sint32 num);

#endif