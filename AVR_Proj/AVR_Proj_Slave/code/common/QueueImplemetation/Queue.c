#include "Queue.h"
#include <string.h>

void Queue_Init(Queue_t* queue, uint8* buffer, uint8 buffer_size)
{
    queue->buffer = &buffer[0];
    queue->buffer_size = buffer_size;

    Queue_Clear(queue);
}

inline void Queue_Clear(Queue_t* queue)
{
    memset(queue->buffer, 0u, queue->buffer_size);
    queue->front = 0u;
    queue->rear = 0u;
    queue->length = 0u;
}

inline Func_ReturnType Queue_Put(Queue_t* queue, uint8 data)
{
    Func_ReturnType ret = RET_OK;

    if((queue->buffer_size - queue->length) <= 0)
    {
        ret = RET_QUEUE_NOT_ENOUGH_SPACE;
    }
    else
    {
        queue->buffer[queue->rear] = data;
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

    return ret;
}

inline Func_ReturnType Queue_PutData(Queue_t* queue, uint8* data, uint8 data_length)
{
    uint8 i = 0;
    Func_ReturnType ret = RET_OK;

    if((queue->buffer_size - queue->length) < data_length)
    {
        ret = RET_QUEUE_NOT_ENOUGH_SPACE;
    }
    else
    {
        Queue_Put(queue, data[i]);
    }

    return ret;
}

inline Func_ReturnType Queue_Pop(Queue_t* queue, uint8* value)
{
    Func_ReturnType ret = RET_QUEUE_EMPTY;

    if(Queue_IsEmpty(queue) != TRUE)
    {
        if(value != NULL)
        {
            *value = queue->buffer[queue->front];
        }
        
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

inline Func_ReturnType Queue_Peek(Queue_t* queue, uint8* value)
{
    Func_ReturnType ret = RET_QUEUE_EMPTY;

    if(Queue_IsEmpty(queue) != TRUE)
    {
        *value = queue->buffer[queue->front];
        ret = RET_OK;
    }

    return ret;
}

inline Func_ReturnType Queue_Length(Queue_t* queue, uint8* value)
{
    Func_ReturnType ret = RET_QUEUE_EMPTY;

    if(Queue_IsEmpty(queue) != TRUE)
    {
        *value = queue->length;
        ret = RET_OK;
    }

    return ret;
}

inline boolean Queue_IsEmpty(Queue_t* queue)
{
    return (queue->length <= 0u);
}


