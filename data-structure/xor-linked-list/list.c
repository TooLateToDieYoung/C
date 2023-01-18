#include "list.h"
#include <stdlib.h>

typedef void fake_t;

typedef struct node_t node_t;
struct node_t {
  void * item;
  fake_t * X;
};

struct list_t {
  node_t * head;
  node_t * tail;
  size_t length;
};

static node_t * _Node_Constructor(void * const item)
{
  node_t * const obj = (node_t*)calloc(1, sizeof(node_t));

  if(obj) obj->item = item;

  return obj;
}

static fake_t * _X(node_t * const P, node_t * const N)
{
  return (fake_t*)( (size_t)(P) ^ (size_t)(N) );
}

static node_t * _N(node_t * const P, fake_t * const X)
{
  return (node_t*)( (size_t)(P) ^ (size_t)(X) );
}

static node_t * _P(node_t * const N, fake_t * const X)
{
  return (node_t*)( (size_t)(N) ^ (size_t)(X) );
}

list_t * List_Constructor(void)
{
  return (list_t*)calloc(1, sizeof(list_t));
}

task_t List_Destructor(list_t * const self)
{
  if(!self) return Fail;
  
  while(self->length) List_TakeHead(self);

  free(self);

  return Success;
}

task_t List_PushHead(list_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * const node = _Node_Constructor(item);

  if(!node) return Fail;

  if(!self->length) self->head = self->tail = node;
  else {
    self->head->X = _X(node, self->head->X); // ? == _X(node, _N(NULL, self->head->X));
    node->X       = self->head;              // ? == _X(NULL, self->head);
    self->head    = node;
  }

  self->length++;

  return Success;
}

task_t List_PushTail(list_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * const node = _Node_Constructor(item);

  if(!node) return Fail;

  if(!self->length) self->head = self->tail = node;
  else {
    self->tail->X = _X(self->tail->X, node); // ? == _X(_P(NULL, self->tail->X), node);
    node->X       = self->tail;              // ? == _X(self->tail, NULL);
    self->tail    = node;
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

  self->length--;

  if(!self->length) self->head = self->tail = NULL;
  else {
    self->head    = self->head->X;           // ? == _N(NULL, self->head->X);
    self->head->X = _N(node, self->head->X); // ? == _X(NULL, _N(node, self->head->X));
  } 

  free(node);

  return item;
}

void * List_TakeTail(list_t * const self)
{
  if(!self) return NULL;

  if(!self->length) return NULL;

  node_t * const node = self->tail;
  
  void * const item = node->item;

  self->length--;

  if(!self->length) self->head = self->tail = NULL;
  else {
    self->tail    = self->tail->X;           // ? == _P(NULL, self->tail->X);
    self->tail->X = _P(node, self->tail->X); // ? == _X(_P(node, self->tail->X), NULL);
  }

  free(node);

  return item;
}

size_t List_Length(list_t const * const self)
{
  return self ? self->length : 0 ;
}
