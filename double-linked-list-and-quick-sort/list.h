#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef enum { False   = 0, True = !False   } bool_t;
typedef enum { Success = 0, Fail = !Success } task_t;

typedef struct list_t list_t;

typedef char (*CompareFunction)(void const * const, void const * const);

list_t * List_Constructor(void);

task_t List_Destructor(list_t * const self);

task_t List_PushHead(list_t * const self, void * const item);

task_t List_PushTail(list_t * const self, void * const item);

void * List_TakeHead(list_t * const self);

void * List_TakeTail(list_t * const self);

size_t List_Length(list_t const * const self);

list_t * List_QuickSort(list_t * const self, CompareFunction cmp);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LIST_H_
