#include <stdlib.h>
#include "stack.h"

struct stack_t
{
  size_t max;
  size_t top;
  void ** array;
};

stack_t * Stack_Constructor(const size_t maxSize)
{
  stack_t * obj = (stack_t*)calloc(1, sizeof(stack_t));

  if(!obj) return NULL;

  obj->max = maxSize;
  obj->array = (void*)calloc(obj->max, sizeof(void*));

  if(!obj->array) {
    Stack_Destructor(obj);
    return NULL; 
  }

  return obj;
}

task_t Stack_Destructor(stack_t * const self)
{
  if(!self) return Fail;

  if(self->array) free(self->array);

  free(self);

  return Success;
}

task_t Stack_Push(stack_t * const self, void * const item)
{
  if(!self) return Fail;

  if(self->top >= self->max) return Fail;

  self->array[self->top++] = item;

  return Success;
}

void * Stack_Take(stack_t * const self)
{
  if(!self) return NULL;

  return self->top ? self->array[--self->top] : NULL ;
}

size_t Stack_Length(stack_t const * const self)
{
  return self ? self->top : 0 ;
}
