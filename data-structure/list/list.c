#include "list.h"
#include <stdlib.h>

typedef struct node_t node_t;
struct node_t {
  void * item;
  node_t * prev;
  node_t * rear;
};

struct list_t {
  node_t * head;
  node_t * tail;
  size_t length;
};

list_t * List_Constructor(void)
{
  return (list_t*)calloc(1, sizeof(list_t));
}

task_t List_Destructor(list_t * const self)
{
  if(!self) return Fail;
  
  while( List_TakeHead(self) != NULL ) { }

  free(self);

  return Success;
}

task_t List_PushHead(list_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * const node = (node_t*)calloc(1, sizeof(node_t));

  if(!node) return Fail;

  node->item = item;

  if(!self->length) self->head = self->tail = node;
  else {
    node->rear = self->head;
    self->head->prev = node;
    self->head = node;
  }

  self->length++;

  return Success;
}

task_t List_PushTail(list_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * const node = (node_t*)calloc(1, sizeof(node_t));

  if(!node) return Fail;

  node->item = item;

  if(!self->length) self->head = self->tail = node;
  else {
    node->prev = self->tail;
    self->tail->rear = node;
    self->tail = node;
  }

  self->length++;

  return Success;
}

void * List_TakeHead(list_t * const self)
{
  if(!self) return NULL;

  if(!self->length) return NULL;

  node_t * const node = self->head;
  
  void * const item = node->item;

  self->head = self->head->rear;

  self->length--;

  free(node);

  return item;
}

void * List_TakeTail(list_t * const self)
{
  if(!self) return NULL;

  if(!self->length) return NULL;

  node_t * const node = self->tail;

  void * const item = node->item;

  self->tail = self->tail->prev;
  
  self->length--;

  free(node);

  return item;
}

static node_t * const _FindNode(node_t * const node, size_t counter)
{
  return counter ? _FindNode(node->rear, counter - 1) : node ;
}

void * List_Index(list_t const * const self, size_t index)
{ 
  if(!self) return NULL;

  return index < self->length ? _FindNode(self->head, index)->item : NULL ;
}

size_t List_Length(list_t const * const self)
{
  return self ? self->length : 0 ;
}
