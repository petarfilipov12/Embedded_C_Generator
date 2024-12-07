#ifndef QUEUE_H
#define QUEUE_H

#include "Types.h"

typedef struct Queue{
    uint8* buffer;
    uint8 buffer_size;
    uint8 front;
    uint8 rear;
    uint8 length;
}Queue_t;

extern void Queue_Init(Queue_t* queue, uint8* buffer, uint8 buffer_size);
extern inline Func_ReturnType Queue_Put(Queue_t* queue, uint8* data, uint8 data_length);
extern inline Func_ReturnType Queue_Pop(Queue_t* queue, uint8* value);
extern inline Func_ReturnType Queue_Peek(Queue_t* queue, uint8* value);
extern inline Func_ReturnType Queue_Length(Queue_t* queue, uint8* value);
extern inline boolean Queue_IsEmpty(Queue_t* queue);

#endif