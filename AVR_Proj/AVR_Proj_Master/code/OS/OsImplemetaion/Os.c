#include "Types.h"
#include "OsHAL.h"
#include "Os.h"
#include "OS_HAL_Interrupt.h"

#define OS_Start main

OS_TASKS_CONFIG()

int OS_Start(void)
{
    OS_CreateTask(Task_10ms, "Task_10ms", 10u,  285u, 2);
    OS_CreateTask(Task_200ms, "Task_200ms", 200u,  110u, 1);

    OS_Interrupt_EnableGlobal();

    OS_Run();

    for(;;)
    {
        //Shoudl not get here
    }

    return 0;
}
