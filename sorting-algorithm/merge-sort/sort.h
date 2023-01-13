#ifndef _SORT_H_
#define _SORT_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum { False   = 0, True = !False   } bool_t;
typedef enum { Success = 0, Fail = !Success } task_t;

typedef char (*CompareFunction)(char, char);

char * Sort(char array[], size_t len, CompareFunction cmp);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _SORT_H_
