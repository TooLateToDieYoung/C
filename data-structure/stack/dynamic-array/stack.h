#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum { Success = 0, Fail = !Success } task_t;

typedef struct stack_t stack_t;

stack_t * Stack_Constructor(const size_t maxSize);

task_t Stack_Destructor(stack_t * const self);

task_t Stack_Push(stack_t * const self, void * const item);

void * Stack_Take(stack_t * const self);

size_t Stack_Length(stack_t const * const self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _STACK_H_
