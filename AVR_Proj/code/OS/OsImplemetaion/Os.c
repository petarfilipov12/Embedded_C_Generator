#include "Types.h"
#include "OsHAL.h"
#include "Os.h"

#define OS_Start main

OS_TASK(Task_100ms, 200u, 85u, 1, OS_GetTaskInitRunnables(Task_100ms), OS_GetTaskCyclicRunnables(Task_100ms))

int OS_Start(void)
{
    OS_CreateTask(Task_100ms, "Task_100ms", 200u,  85u, 1);

    OS_Run();

    for(;;)
    {
        //Shoudl not get here
    }

    return 0;
}
