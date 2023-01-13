#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum { Success = 0, Fail = !Success } task_t;

typedef struct queue_t queue_t;

queue_t * Queue_Constructor(void);

task_t Queue_Destructor(queue_t * const self);

task_t Queue_Push(queue_t * const self, void * const item);

void * Queue_Take(queue_t * const self);

size_t Queue_Length(queue_t const * const self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _QUEUE_H_
