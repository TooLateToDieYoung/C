#include "list.h"
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t {
  void * item;
  node_t * P;
  node_t * N;
};

struct list_t {
  node_t * head;
  node_t * tail;
  size_t length;
};

static node_t * _Node_Constructor(void * const item)
{
  node_t * const obj = (node_t*)calloc(1, sizeof(node_t));

  if(!obj) return NULL;

  obj->item = item;

  return obj;
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

  node_t * node = _Node_Constructor(item);

  if(!node) return Fail;

  if(!self->length) self->head = self->tail = node;
  else {
    node->N = self->head;
    self->head->P = node;
    self->head = node;
  }

  self->length++;

  return Success;
}

task_t List_PushTail(list_t * const self, void * const item)
{
  if(!self) return Fail;

  node_t * node = _Node_Constructor(item);

  if(!node) return Fail;

  if(!self->length) self->head = self->tail = node;
  else {
    node->P = self->tail;
    self->tail->N = node;
    self->tail = node;
  }

  self->length++;

  return Success;
}

void * List_TakeHead(list_t * const self)
{
  if(!self || !self->length) return NULL;

  node_t * node = self->head;

  void * const result = node->item;

  if(--self->length) self->head = node->N;
  else self->head = self->tail = NULL;

  free(node);

  return result;
}

void * List_TakeTail(list_t * const self)
{
  if(!self || !self->length) return NULL;

  node_t * node = self->tail;

  void * const result = node->item;

  if(--self->length) self->tail = node->P;
  else self->head = self->tail = NULL;

  free(node);

  return result;
}

size_t List_Length(list_t const * const self)
{
  return self ? self->length : 0 ;
}

static void _Node_Swap(node_t * const a, node_t * const b)
{
  void * const temp = a->item;
  a->item = b->item;
  b->item = temp;
}

static void _Node_QuickSort(node_t * const head, node_t * const tail, CompareFunction cmp)
{
  if(!head || !tail || head == tail) return;

  node_t * Nptr = head->N;
  node_t * Pptr = tail;

  while( Nptr != Pptr->N ) {
    if( cmp(head->item, Pptr->item) == +1 ) { Pptr = Pptr->P; }
    else { _Node_Swap(Nptr, Pptr); Nptr = Nptr->N; }
  }

  if(head != Pptr) _Node_Swap(head, Pptr);

  _Node_QuickSort(head, Pptr, cmp);
  _Node_QuickSort(Nptr, tail, cmp);
}

list_t * List_QuickSort(list_t * const self, CompareFunction cmp)
{
  if(!self || !cmp) return NULL;

  _Node_QuickSort(self->head, self->tail, cmp);

  // ? bubble sort
  //for(node_t * i = self->head; i; i = i->N) 
  //  for(node_t * j = i->N; j; j = j->N)
  //    if(cmp(i->item, j->item) == +1) 
  //      _Node_Swap(i, j);

  return self;
}
