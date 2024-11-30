#include "Queue.h"
#include <string.h>

void Queue_Init(Queue_t* queue, uint8* buffer, uint8 buffer_size)
{
    queue->buffer = &buffer[0];
    queue->buffer_size = buffer_size;
    memset(queue->buffer, 0u, buffer_size);
    queue->front = 0u;
    queue->rear = 0u;
    queue->length = 0u;
}

Func_ReturnType Queue_Put(Queue_t* queue, uint8* data, uint8 data_length)
{
    uint8 i = 0;
    Func_ReturnType ret = RET_OK;

    if((queue->buffer_size - queue->length) < data_length)
    {
        ret = RET_QUEUE_NOT_ENOUGH_SPACE;
    }
    else
    {
        for(i=0; i<data_length; i++)
        {
            queue->buffer[queue->rear] = data[i];
            queue->length++;

            if(queue->rear >= (queue->buffer_size - 1))
            {
                queue->rear = 0u;
            }
            else
            {
                queue->rear++;
            }
        }
    }

    return ret;
}

Func_ReturnType Queue_Pop(Queue_t* queue, uint8* value)
{
    Func_ReturnType ret = RET_QUEUE_EMPTY;

    if(Queue_IsEmpty(queue) != TRUE)
    {
        *value = queue->buffer[queue->front];
        queue->length--;

        if(queue->front >= (queue->buffer_size - 1))
        {
            queue->front = 0u;
        }
        else
        {
            queue->front++;
        }

        ret = RET_OK;
    }

    return ret;
}

boolean Queue_IsEmpty(Queue_t* queue)
{
    return (queue->length <= 0u);
}


