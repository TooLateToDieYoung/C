#include "queue.h"
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t {
  void   * item;
  node_t * prev;
  node_t * rear;
};

struct queue_t {
  node_t * head;
  node_t * tail;
  size_t length;
};

queue_t * Queue_Constructor(void)
{
  return (queue_t*)calloc(1, sizeof(queue_t));
}

task_t Queue_Destructor(queue_t * const self)
{
  if(!self) return Fail;

  while( Queue_Take(self) ) { }

  free(self);

  return Success;
}

task_t Queue_Push(queue_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * const node = (node_t*)calloc(1, sizeof(node_t));

  if(!node) return Fail;

  node->item = item;
  
  if(!self->length) self->head = self->tail = node;
  else {
    self->tail->rear = node;
    node->prev = self->tail;
    self->tail = node;
  }

  self->length++;

  return Success;
}

void * Queue_Take(queue_t * const self)
{
  if(!Queue_Length(self)) return NULL;

  node_t * const node = self->head;
  void * const result = node->item;

  if(self->length == 1) self->head = self->tail = NULL;
  else {
    self->head = self->head->rear;
    self->head->prev = NULL;
  }

  self->length--;
  
  free(node);

  return result;
}

size_t Queue_Length(queue_t const * const self)
{
  return self ? self->length : 0 ;
}
