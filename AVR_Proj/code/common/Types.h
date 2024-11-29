#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define NULL 0

typedef int8_t sint8;
typedef uint8_t uint8;

typedef int16_t sint16;
typedef uint16_t uint16;

typedef int32_t sint32;
typedef uint32_t uint32;

typedef int64_t sint64;
typedef uint64_t uint64;

typedef uint8 boolean;
#define TRUE    ((uint8)1u)
#define FALSE   ((uint8)0u)

typedef uint8 Func_ReturnType;
#define RET_OK      ((uint8)0u)
#define RET_NOT_OK  ((uint8)1u)
#define RET_BUSY    ((uint8)2u)

#endif