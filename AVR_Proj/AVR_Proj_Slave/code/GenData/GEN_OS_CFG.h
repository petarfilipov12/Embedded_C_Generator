#ifndef GEN_OS_CFG_H
#define GEN_OS_CFG_H

#define OS_Task_10ms_Prio2_InitRunnables	\
ADC_Service_Init();	\
SPI_Service_Init();	\
UART_Service_Init();	\
WDT_Service_Init();

#define OS_Task_10ms_Prio2_CyclicRunnables	\
WDT_Service_Cyclic();	\
ADC_Service_Cyclic();	\
UART_Service_Cyclic();

#define OS_Task_200ms_Prio1_InitRunnables	\
GPT_Service_Init();	\
PWM_Service_Init();	\
DIO_Service_Init();	\
LCD_Driver_Init();	\
CompLedIndicator_Init();

#define OS_Task_200ms_Prio1_CyclicRunnables	\
CompLedIndicator_Cyclic();

#define OS_TASKS_CONFIG()	\
OS_TASK(OS_Task_10ms_Prio2, 10u, 285u, 2u, OS_Task_10ms_Prio2_InitRunnables, OS_Task_10ms_Prio2_CyclicRunnables)	\
OS_TASK(OS_Task_200ms_Prio1, 200u, 110u, 1u, OS_Task_200ms_Prio1_InitRunnables, OS_Task_200ms_Prio1_CyclicRunnables)

#define OS_CREATE_TASKS()	\
OS_CreateTask(OS_Task_10ms_Prio2, 10u, 285u, 2u);	\
OS_CreateTask(OS_Task_200ms_Prio1, 200u, 110u, 1u);

#endif