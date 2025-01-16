/* DO NOT REMOVE COMMENT - GEN INCLUDE SECTION */
#include "GEN_CompSensor_SERVER_PORTS_CFG.h"
#include "GEN_CompSensor_CLIENT_PORTS_CFG.h"
#include "CompSensor.h"
/* DO NOT REMOVE COMMENT - GEN END SECTION */

#define BUFFER_SIZE 2
uint8 buffer[BUFFER_SIZE] = {0};
uint8 current_buffer_size = 0;

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-VARS SECTION */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN SERVER PORTS-FUNCS SECTION */
/* DO NOT REMOVE COMMENT - GEN END SECTION */

/* DO NOT REMOVE COMMENT - GEN RUNNABLES SECTION */
/* DO NOT REMOVE COMMENT - GEN START FUNC */
void CompSensor_Cyclic(void)
{
    uint8 sensor_val = 0;
    uint8 i = 0;
    uint8 avg = 0;
    uint32 sum = 0;

    if(RET_OK == CompSensor_ADC_ReadPin(ADC_Service_ADC_PIN_0_Id, &sensor_val))
    {
        CompSensor_PWM_SetPin(PWM_Service_PWM_PIN_0_Id, sensor_val);
        if(current_buffer_size < BUFFER_SIZE)
        {
            buffer[current_buffer_size] = sensor_val;
            current_buffer_size++;
        }
    }

    if(current_buffer_size >= BUFFER_SIZE)
    {
        for(i = 0; i < BUFFER_SIZE; i++)
        {
            sum += buffer[i];
        }
        avg = (uint8)(sum / (uint32)BUFFER_SIZE);

        CompSensor_SPI_Transmit(SPI_Service_SPI_0_Id, &avg, NULL, 1u);

        current_buffer_size = 0;
    }
}
/* DO NOT REMOVE COMMENT - GEN END FUNC */
/* DO NOT REMOVE COMMENT - GEN END SECTION */