#ifndef _HASH_H_
#define _HASH_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // cplusplus

typedef enum { Success = 0, Fail = !Success } task_t;

typedef struct hash_t hash_t;

typedef size_t (*HashFunction)(char const * const key, size_t len);

hash_t * Hash_Constructor(size_t len, HashFunction func);

task_t Hash_Destructor(hash_t * const self);

task_t Hash_Insert(hash_t * const self, char const * const key, size_t len, void * const item);

void * Hash_Delete(hash_t * const self, char const * const key, size_t len);

void * Hash_Index(hash_t * const self, char const * const key, size_t len);

#ifdef __cplusplus
}
#endif // cplusplus

#endif // _HASH_H_
