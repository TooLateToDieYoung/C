#include "queue.h"
#include <stdlib.h>

struct queue_t {
  size_t  size;
  size_t  head;
  size_t  tail;
  void ** array;
};

queue_t * Queue_Constructor(const size_t maxSize)
{
  if(!maxSize) return NULL;

  queue_t * const obj = (queue_t*)calloc(1, sizeof(queue_t));

  if(!obj) return NULL;

  obj->size  = maxSize + 1;
  obj->array = (void**)calloc(obj->size, sizeof(void*));

  if(!obj->array) {
    Queue_Destructor(obj);
    return NULL;
  }

  return obj;
}

task_t Queue_Destructor(queue_t * const self)
{
  if(!self) return Fail;

  if(self->array) free(self->array);

  free(self);

  return Success;
}

task_t Queue_Push(queue_t * const self, void * const item)
{
  if(!self) return Fail;

  if(Queue_Length(self) == self->size - 1) return Fail; // ? is full

  self->array[self->tail++] = item;

  self->tail %= self->size;

  return Success;
}

void * Queue_Take(queue_t * const self)
{
  if(!Queue_Length(self)) return NULL;

  void * const result = self->array[self->head++];

  self->head %= self->size;

  return result;
}

size_t Queue_Length(queue_t const * const self)
{
  if(!self) return 0;
  return 
    self->tail < self->head ? 
    self->size - self->head + self->tail : 
    self->head - self->tail ;
}
