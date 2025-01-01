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
#define RET_OK                      ((uint8)0u)
#define RET_NOT_OK                  ((uint8)1u)
#define RET_BUSY                    ((uint8)2u)
#define RET_PENDING                 ((uint8)6u)
#define RET_READY                   ((uint8)6u)

#define RET_ADC_ERROR               ((uint8)7u)

#define RET_QUEUE_IN_USE            ((uint8)3u)
#define RET_QUEUE_NOT_ENOUGH_SPACE  ((uint8)4u)
#define RET_QUEUE_EMPTY             ((uint8)5u)

#define PIN_INPUT   ((uint8)0u)
#define PIN_OUTPUT  ((uint8)1u)
#define PIN_LOW     ((uint8)0u)
#define PIN_HIGH    ((uint8)1u)

#define GPT_MODE_NORMAL ((uint8)0u)
#define GPT_MODE_PWM    ((uint8)1u)

#endif