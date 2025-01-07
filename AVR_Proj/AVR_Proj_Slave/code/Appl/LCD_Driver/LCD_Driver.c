/* DO NOT REMOVE COMMENT - GEN INCLUDE SECTION */
#include "GEN_LCD_Driver_SERVER_PORTS_CFG.h"
#include "GEN_LCD_Driver_CLIENT_PORTS_CFG.h"
#include "LCD_Driver.h"
/* DO NOT REMOVE COMMENT - GEN END SECTION */

#include "OS_Delay.h"
#include "OS_Interrupt.h"

#define LCD_MODE_COMMAND    PIN_LOW
#define LCD_MODE_DATA       PIN_HIGH

#define LCD_COMMAND_4BITMODE    0x28
#define LCD_COMMAND_DISPLAYON   0x0C
#define LCD_COMMAND_SETCURSOR   0x80
#define LCD_COMMAND_CLEAR       0x01

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-VARS SECTION */
uint8 LCD_Driver_LCD_Status;
/* DO NOT REMOVE COMMENT - GEN END SECTION */

static void LCD_SendCommand(uint8 value);
static void LCD_WriteByte(uint8 value);
static void LCD_Send(uint8 value, uint8 mode);
static void LCD_Write4Bits(uint8 value);
static void LCD_PulseEnable(void);

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-FUNCS SECTION */
/* DO NOT REMOVE COMMENT - GEN START FUNC */
Func_ReturnType LCD_Driver_LCD_Begin()
{
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_RW_Id, PIN_LOW);
    OS_Delay_us(1000);

    LCD_Driver_PWM_Set_Pin(PWM_Service_PWM_LCD_V0_Id, 90);
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_RS_Id, PIN_LOW);
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_E_Id, PIN_LOW);

    OS_Interrupt_DisableGlobal();
    LCD_SendCommand(LCD_COMMAND_4BITMODE);
    OS_Delay_us(4500);
    LCD_SendCommand(LCD_COMMAND_4BITMODE);
    OS_Delay_us(4500);
    LCD_SendCommand(LCD_COMMAND_4BITMODE);
    OS_Delay_us(150);

    LCD_SendCommand(LCD_COMMAND_4BITMODE);
    OS_Interrupt_EnableGlobal();

    LCD_SendCommand(LCD_COMMAND_DISPLAYON);
    OS_Delay_us(10);

    LCD_Driver_LCD_Clear();

    return RET_OK;
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
Func_ReturnType LCD_Driver_LCD_Clear()
{
    LCD_SendCommand(LCD_COMMAND_CLEAR);
    OS_Delay_us(10000);

    return RET_OK;
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
Func_ReturnType LCD_Driver_LCD_SetCursor(uint8 line, uint8 pos)
{
    LCD_SendCommand((LCD_COMMAND_SETCURSOR | (line << 6)) + pos);

    return RET_OK;
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
Func_ReturnType LCD_Driver_LCD_WriteString(uint8* data, uint8 data_length)
{
    uint8 i = 0;

    for(i = 0; i < data_length; i++)
    {
        LCD_WriteByte(data[i]);
    }

    return RET_OK;
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */

/* DO NOT REMOVE COMMENT - GEN START FUNC */
Func_ReturnType LCD_Driver_LCD_WriteNumber(sint32 num)
{
    char snum[16];
    sprintf(snum, "%d", num);

    return LCD_Driver_LCD_WriteString(&snum[0], strlen(snum));
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN RUNNABLES SECTION */
/* DO NOT REMOVE COMMENT - GEN START FUNC */
void LCD_Driver_Init(void)
{
    LCD_Driver_LCD_Status = LCD_OFF;
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

static void LCD_SendCommand(uint8 value)
{
    LCD_Send(value, LCD_MODE_COMMAND);
}

static void LCD_WriteByte(uint8 value)
{
    LCD_Send(value, LCD_MODE_DATA);
}

static void LCD_Send(uint8 value, uint8 mode)
{
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_RW_Id, PIN_LOW);
    OS_Delay_us(1000);

    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_RS_Id, mode);

    LCD_Write4Bits(value >> 4);
    LCD_Write4Bits(value);

    OS_Delay_us(1000);
}

static void LCD_Write4Bits(uint8 value)
{
    // LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D4_Id, ((value & 0x01u)? PIN_HIGH : PIN_LOW));
    // LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D5_Id, (((value >> 1) & 0x01u)? PIN_HIGH : PIN_LOW));
    // LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D6_Id, (((value >> 2) & 0x01u)? PIN_HIGH : PIN_LOW));
    // LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D7_Id, (((value >> 3) & 0x01u)? PIN_HIGH : PIN_LOW));

    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D4_Id, (value & 0x01u));
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D5_Id, ((value >> 1) & 0x01u));
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D6_Id, ((value >> 2) & 0x01u));
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_D7_Id, ((value >> 3) & 0x01u));

    OS_Delay_us(10);

    LCD_PulseEnable();
}

static void LCD_PulseEnable(void)
{
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_E_Id, PIN_LOW);
    OS_Delay_us(1);
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_E_Id, PIN_HIGH);
    OS_Delay_us(1);
    LCD_Driver_DIO_Write_Pin(DIO_Service_DIO_LCD_E_Id, PIN_LOW);
    OS_Delay_us(100);
}