#include "tree.h"
#include <stdlib.h>

#define _L(curr) ( (curr) << 1 | 0U )
#define _R(curr) ( (curr) << 1 | 1U )
#define _P(curr) ( (curr) >> 1 )

static void _Swap(void * * const a, void * * const b)
{
  static void * temp = NULL;
  temp = *a;
  *a = *b;
  *b = temp;
}

struct tree_t {
  CompareFunction cmp;
  size_t  size;
  size_t  tail;
  void ** buffer; // It means: void * buffer[];
};

tree_t * Tree_Constructor(CompareFunction cmp, size_t size)
{
  if(!cmp || !size) return NULL;

  tree_t * const obj = (tree_t*)malloc(sizeof(tree_t));

  if(!obj) return NULL;

  obj->cmp  = cmp;
  obj->size = size + 1;
  obj->tail = 1;
  obj->buffer = (void**)calloc(obj->size, sizeof(void*));

  if(!obj->buffer) {
    Tree_Destructor(obj);
    return NULL;
  }

  return obj;
}

task_t Tree_Destructor(tree_t * const self)
{
  if(!self) return Fail;

  if(self->buffer) free(self->buffer);

  free(self);

  return Success;
}

static void _Tree_PushHeapfy(tree_t * const self, size_t curr)
{
  if( !_P(curr) ) return;

  if( self->cmp(self->buffer[_P(curr)], self->buffer[curr]) != 1 ) return;

  _Swap(&self->buffer[_P(curr)], &self->buffer[curr]);

  _Tree_PushHeapfy(self, _P(curr));
}

task_t Tree_Push(tree_t * const self, void * const item)
{
  if(Tree_isFull(self)) return Fail;

  self->buffer[self->tail] = item;

  _Tree_PushHeapfy(self, self->tail);

  self->tail++;

  return Success;
}

static void _Tree_TakeHeapfy(tree_t * const self, size_t curr)
{
  size_t index = curr;

  if(
    self->tail > _L(curr) && 
    self->cmp(self->buffer[index], self->buffer[_L(curr)]) == 1
  ) index = _L(curr);

  if(
    self->tail > _R(curr) && 
    self->cmp(self->buffer[index], self->buffer[_R(curr)]) == 1
  ) index = _R(curr);

  if( curr == index ) return;

  _Swap(&self->buffer[curr], &self->buffer[index]);

  _Tree_TakeHeapfy(self, index);
}

void * Tree_Take(tree_t * const self)
{
  if(Tree_isEmpty(self)) return NULL;

  self->tail--;

  void * result = self->buffer[1];

  self->buffer[1] = self->buffer[self->tail];

  _Tree_TakeHeapfy(self, 1);

  return result;
}

bool_t Tree_isEmpty(tree_t const * const self)
{
  return self->tail == 1;
}

bool_t Tree_isFull(tree_t const * const self)
{
  return self->tail == self->size;
}
