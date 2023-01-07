#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

#define _BIT(offset)      ( 1U << (offset) )
#define _MASK(reg, bits)  ( (reg) & (bits) )

// ? Use typedef enum to avoid to conflicts.

typedef enum { False   = 0, True = !False   } bool_t;

typedef enum { Success = 0, Fail = !Success } task_t;

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t ;

typedef signed   int   sint32_t;
typedef signed   short sint16_t;
typedef signed   char  sint8_t ;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _COMMON_H_
