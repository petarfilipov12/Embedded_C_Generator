#include "CompSensor.h"
#include "SPI_Service.h"

void CompSensor_Cyclic_100ms(void)
{
    uint8 sensor_val = 0;

    if(RET_OK == ADC_Service_Read_Pin(ADC_Service_PIN_0_ID, &sensor_val))
    {
        PWM_Service_Set_Pin(PWM_Service_PIN_0_ID, sensor_val);
        SPI_Service_Transmit(SPI_Service_SPI_MASTER_SPI_0_ID, &sensor_val, NULL, 1u);
    }
}