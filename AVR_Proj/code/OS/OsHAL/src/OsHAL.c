#include "OsHAL.h"

uint8_t OsHAL_CreateTask(Os_TaskType_t pTaskP, char* TaskName, uint8_t u8PeriodP, uint32_t u32StackSizeP, uint8_t u8PriorityP)
{
    BaseType_t xreturnL = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
    uint8_t u8retL = 0;

    (void)u8PeriodP;

    xreturnL = xTaskCreate(
        pTaskP,
        TaskName,
        (const uint16_t)u32StackSizeP,
        NULL,
        tskIDLE_PRIORITY + (UBaseType_t)u8PriorityP,
        NULL);
    
    //TODO Rethink
    if(pdPASS == xreturnL)
    {
        u8retL = 1;
    }

    return u8retL;
}