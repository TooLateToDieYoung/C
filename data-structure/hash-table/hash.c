#include "hash.h"
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;
struct node_t {
  char * key;
  size_t len;
  void * item;
  node_t * next;
};

struct hash_t {
  node_t ** list;
  size_t len;
  HashFunction func;
};

hash_t * Hash_Constructor(size_t len, HashFunction func)
{
  if(!len || !func) return NULL;

  hash_t * const obj = (hash_t*)calloc(1, sizeof(hash_t));

  if(!obj) return NULL;

  obj->len  = len;
  obj->func = func;
  obj->list = (node_t**)calloc(obj->len, sizeof(node_t*));

  if(!obj->list) {
    Hash_Destructor(obj);
    return NULL;
  }

  return obj;
}

task_t Hash_Destructor(hash_t * const self)
{
  if(!self) return Fail;

  if(!self->list) goto __End;

  node_t * temp = NULL;
  for(size_t i = 0; i < self->len; ++i) {
    while(self->list[i]) {
      temp = self->list[i]->next;
      free(self->list[i]->key);
      free(self->list[i]);
      self->list[i] = temp;
    }
  }

  free(self->list);

__End:
  free(self);
  return Success;
}

task_t Hash_Insert(hash_t * const self, char const * const key, size_t len, void * const item)
{
  if(!self) return Fail;

  node_t * const node = (node_t*)calloc(1, sizeof(node_t));

  if(!node) return Fail;

  node->item = item;
  node->len  = len + 1;
  node->key  = (char*)calloc(node->len, sizeof(char));

  if(!node->key) {
    free(node);
    return Fail;
  }

  strncpy(node->key, key, len);

  const size_t order = self->func(key, len);

  if(!self->list[order]) self->list[order] = node;
  else {
    node_t * curr = self->list[order];
    while(curr->next) curr = curr->next;
    curr->next = node;
  }

  return Success;
}

void * Hash_Delete(hash_t * const self, char const * const key, size_t len)
{
  if(!self) return NULL;

  const size_t order = self->func(key, len);

  node_t * prev = NULL;
  node_t * curr = self->list[order];

  while( curr && strncmp(curr->key, key, len) ) {
    prev = curr;
    curr = curr->next;
  }

  if(!curr) return NULL;

  void * item = curr->item;

  if(prev) prev->next = curr->next;

  free(curr->key);
  free(curr);

  return item;
}

void * Hash_Index(hash_t * const self, char const * const key, size_t len)
{
  if(!self) return NULL;

  const size_t order = self->func(key, len);

  node_t * curr = self->list[order];

  while( curr && strncmp(curr->key, key, len) ) curr = curr->next;

  return curr ? curr->item : NULL ;
}
