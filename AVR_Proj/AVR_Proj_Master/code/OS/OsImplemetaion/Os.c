#include "Os.h"
#include "OS_Interrupt.h"

#define OS_Start main

OS_TASKS_CONFIG()

int OS_Start(void)
{
    OS_CREATE_TASKS()

    OS_Interrupt_EnableGlobal();

    OS_Run();

    for(;;)
    {
        //Shoudl not get here
    }

    return 0;
}
