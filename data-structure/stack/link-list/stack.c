#include <stdlib.h>
#include "stack.h"

typedef struct node_t node_t;
struct node_t {
  void * item;
  node_t * next;
};

struct stack_t {
  node_t * top;
  size_t length;
};

stack_t * Stack_Constructor()
{
  return (stack_t*)calloc(1, sizeof(stack_t));
}

task_t Stack_Destructor(stack_t * const self)
{
  if(!self) return Fail;

  while( Stack_Take(self) ) { }

  free(self);

  return Success;
}

task_t Stack_Push(stack_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * node = (node_t*)calloc(1, sizeof(node_t));

  if(!node) return Fail;

  node->item = item;
  node->next = self->top;

  self->top = node;
  self->length++;

  return Success;
}

void * Stack_Take(stack_t * const self)
{
  if(!self) return NULL;

  if(!self->length) return NULL;

  node_t * node = self->top;
  void * item = node->item;

  self->top = self->top->next;
  self->length--;

  free(node);

  return item;
}

size_t Stack_Length(stack_t const * const self)
{
  return self ? self->length : 0 ;
}
