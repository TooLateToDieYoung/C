#ifndef _TREE_H_
#define _TREE_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum { Success = 0, Fail = !Success } task_t;
typedef enum { False   = 0, True = !False   } bool_t;

typedef struct tree_t tree_t;

typedef char (*CompareFunction)(void const * const a, void const * const b);

tree_t * Tree_Constructor(CompareFunction cmp, size_t size);

task_t Tree_Destructor(tree_t * const self);

task_t Tree_Push(tree_t * const self, void * const item);

void * Tree_Take(tree_t * const self);

bool_t Tree_isEmpty(tree_t const * const self);

bool_t Tree_isFull(tree_t const * const self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TREE_H_
