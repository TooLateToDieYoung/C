#include "tree.h"
#include <stdlib.h>

typedef enum { NodeR, NodeB } color_t;

typedef struct node_t node_t;

struct node_t {
  void * item;
  node_t * P;
  node_t * L;
  node_t * R;
  color_t color;
};

struct tree_t {
  node_t * root;
  CompareFunction cmp;
};

static node_t * _Node_Constructor(void * const item)
{
  node_t * const obj = (node_t*)calloc(1, sizeof(node_t));

  if(!obj) return NULL;

  obj->item  = item;
  obj->color = NodeR; // ? default value
  
  return obj;
}
tree_t * Tree_Constructor(CompareFunction cmp)
{
  if(!cmp) return NULL;

  tree_t * const obj = (tree_t*)calloc(1, sizeof(tree_t));

  if(!obj) return NULL;

  obj->cmp = cmp;

  return obj;
}

static void _Node_Destructor(node_t * const self)
{
  if(!self) return;

  _Node_Destructor(self->L);
  _Node_Destructor(self->R);

  free(self);
}
task_t Tree_Destructor(tree_t * const self)
{
  if(!self) return Fail;

  _Node_Destructor(self->root);

  free(self);

  return Success;
}

static node_t * _Node_FarR(node_t * const self)
{
  return self->R ? _Node_FarR(self->R) : self ;
}
void * Tree_FarR(tree_t const * const self)
{
  return self && self->root ? _Node_FarR(self->root)->item : NULL ;
}

static node_t * _Node_FarL(node_t * const self)
{
  return self->L ? _Node_FarL(self->L) : self ;
}
void * Tree_FarL(tree_t const * const self)
{
  return self && self->root ? _Node_FarL(self->root)->item : NULL ;
}

static node_t * _Node_Adjust(node_t * const self)
{
  // TODO: red-black tree check & rotate.

  return self->P ? _Node_Adjust(self->P) : self ;
}
static node_t * _Node_Insert(node_t * const self, node_t * const add, CompareFunction cmp)
{
  switch (cmp(self->item, add->item)) {
    case -1: {
      if(self->L) return _Node_Insert(self->L, add, cmp);
      self->L = add;
      add->P = self;
      return _Node_Adjust(add);
    }
    case +1: {
      if(self->R) return _Node_Insert(self->R, add, cmp);
      self->R = add;
      add->P = self;
      return _Node_Adjust(add);
    }
    default: {
      _Node_Destructor(add);
      return _Node_Adjust(self); // ! Error case
    }
  }
}
task_t Tree_Insert(tree_t * const self, void * const item)
{
  if(!self) return Fail;

  if(Tree_isContain(self, item)) return Success;

  node_t * const node = _Node_Constructor(item);

  if(!node) return Fail;

  self->root = Tree_isEmpty(self) ? node : _Node_Insert(self->root, node, self->cmp);

  return Success;
}

static node_t * _Node_Sink(node_t * const self)
{
  static node_t * temp = NULL;

  temp = self;
  if     (self->L) temp = _Node_FarR(self->L);
  else if(self->R) temp = _Node_FarL(self->R);

  if(self != temp) {
    self->item = temp->item;
    return _Node_Sink(temp);
  }

  temp = self->P;
  if(temp->L == self) temp->L = NULL;
  else                temp->R = NULL;
  free(self);
  return _Node_Adjust(temp);
}
static node_t * _Node_Remove(node_t * const self, void * const item, CompareFunction cmp)
{
  switch (cmp(self->item, item)) {
    case -1: return _Node_Remove(self->L, item, cmp);
    case +1: return _Node_Remove(self->R, item, cmp);
    default: return _Node_Sink(self);
  }
}
task_t Tree_Remove(tree_t * const self, void * const item)
{
  if(!self) return Fail;

  if(!Tree_isContain(self, item)) return Success;

  // ? Check if the item is at this tree's root.
  if(self->cmp(self->root->item, item)) {
    self->root = _Node_Remove(self->root, item, self->cmp);
    return Success;
  }
  
  // ? The item is at this tree's root but the root still has leaves.
  if(self->root->L || self->root->R) {
    self->root = _Node_Sink(self->root);
    return Success;
  }
  
  // ? Last case: size of tree is 1 && root is exactly item. 
  _Node_Destructor(self->root);
  self->root = NULL;

  return Success;
}

bool_t Tree_isEmpty(tree_t const * const self)
{
  return self ? self->root == NULL : True ;
}

static bool_t _Node_isContain(node_t const * const self, void * const item, CompareFunction cmp)
{
  if(!self) return False;

  switch (cmp(self->item, item)) {
    case -1: return _Node_isContain(self->L, item, cmp);
    case +1: return _Node_isContain(self->R, item, cmp);
    case  0: return True;
    default: return False;
  }
}
bool_t Tree_isContain(tree_t const * const self, void * const item)
{
  return self ? _Node_isContain(self->root, item, self->cmp) : False ;
}

static size_t _Max(size_t a, size_t b)
{
  return a > b ? a : b ;
}
static size_t _Node_Height(node_t const * const self)
{
  return self ? _Max(_Node_Height(self->L), _Node_Height(self->R)) + 1 : 0 ;
}
size_t Tree_Height(tree_t const * const self)
{
  return self ? _Node_Height(self->root) : 0 ;
}

static size_t _Node_Size(node_t const * const self)
{
  return self ? _Node_Size(self->L) + _Node_Size(self->R) + 1 : 0 ;
}
size_t Tree_Size(tree_t const * const self)
{
  return self ? _Node_Size(self->root) : 0 ;
}
