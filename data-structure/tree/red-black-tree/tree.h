#ifndef _TREE_H_
#define _TREE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef enum { Success = 0, Fail = !Success } task_t;
typedef enum { False   = 0, True = !False   } bool_t;

typedef struct tree_t tree_t;

typedef char (*CompareFunction)(void const * const a, void const * const b);

tree_t * Tree_Constructor(CompareFunction cmp);

task_t Tree_Destructor(tree_t * const self);

void * Tree_FarR(tree_t const * const self);

void * Tree_FarL(tree_t const * const self);

task_t Tree_Insert(tree_t * const self, void * const item);

task_t Tree_Remove(tree_t * const self, void * const item);

bool_t Tree_isEmpty(tree_t const * const self);

bool_t Tree_isContain(tree_t const * const self, void * const item);

size_t Tree_Height(tree_t const * const self);

size_t Tree_Size(tree_t const * const self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TREE_H_
