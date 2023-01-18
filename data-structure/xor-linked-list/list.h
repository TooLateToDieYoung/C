#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // cplusplus

typedef enum { Success = 0, Fail = !Success } task_t;

typedef struct list_t list_t;

list_t * List_Constructor(void);

task_t List_Destructor(list_t * const self);

task_t List_PushHead(list_t * const self, void * const item);

task_t List_PushTail(list_t * const self, void * const item);

void * List_TakeHead(list_t * const self);

void * List_TakeTail(list_t * const self);

size_t List_Length(list_t const * const self);

#ifdef __cplusplus
}
#endif // cplusplus

#endif // _LIST_H_
