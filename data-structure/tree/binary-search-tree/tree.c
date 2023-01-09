#include "tree.h"
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t {
  void * item;
  node_t * P;
  node_t * L;
  node_t * R;
};

struct tree_t {
  node_t * root;
  CompareFunction cmp;
};

/* Static Helper Function Begin ------------------------------------------------*/

// * Tree_Constructor
static node_t * _Node_Constructor(void * const item, node_t * const parent);

// * Tree_Destructor
static void _Node_Destructor(node_t * const self);

// * Tree_FarR
static node_t * _Node_FarR(node_t * const self);

// * Tree_FarL
static node_t * _Node_FarL(node_t * const self);

// * Tree_Insert
static task_t _Node_Insert(node_t * const self, node_t * const add, CompareFunction cmp);

// * Tree_Remove
static task_t _Node_Sink(node_t * const self, CompareFunction cmp);
static task_t _Node_Remove(node_t * const self, void * const item, CompareFunction cmp);

// * Tree_isContain
static bool_t _Node_isContain(node_t const * const self, void * const item, CompareFunction cmp);

// * Tree_Height
static size_t _Max(size_t a, size_t b);
static size_t _Node_Height(node_t const * const self);

// * Tree_Size
static size_t _Node_Size(node_t const * const self);

/* --------------------------------------------------- Static Helper Function End */

/* Constructor */
static node_t * _Node_Constructor(void * const item, node_t * const parent)
{
  node_t * const obj = (node_t*)calloc(1, sizeof(node_t));

  if(!obj) return NULL;

  obj->P    = parent;
  obj->item = item;

  return obj;
}

tree_t * Tree_Constructor(CompareFunction cmp)
{
  if(!cmp) return NULL;

  tree_t * const obj = (tree_t*)calloc(1, sizeof(tree_t));

  if(!obj) return NULL;

  obj->cmp  = cmp;

  return obj;
}

/* Destructor */
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


/* FarR */
static node_t * _Node_FarR(node_t * const self)
{
  return self->R ? _Node_FarR(self->R) : self ;
}

void * Tree_FarR(tree_t const * const self)
{
  return Tree_isEmpty(self) ? NULL : _Node_FarR(self->root)->item ; 
}

/* FarL */
static node_t * _Node_FarL(node_t * const self)
{
  return self->L ? _Node_FarL(self->L) : self ;
}

void * Tree_FarL(tree_t const * const self)
{
  return Tree_isEmpty(self) ? NULL : _Node_FarL(self->root)->item ; 
}

/* Insert */
static task_t _Node_Insert(node_t * const self, node_t * const add, CompareFunction cmp)
{
  switch (cmp(self->item, add->item)) {

    case -1: {
      if(self->L) return _Node_Insert(self->L, add, cmp);
      self->L = add;
      add->P = self;
      return Success;
    }

    case +1: {
      if(self->R) return _Node_Insert(self->R, add, cmp);
      self->R = add;
      add->P = self;
      return Success;
    }
    
    default: {
      _Node_Destructor(add);
      return Fail;
    }

  }
}

task_t Tree_Insert(tree_t * const self, void * const item)
{
  if(!self) return Fail;

  if(Tree_isContain(self, item)) return Fail;

  node_t * const node = _Node_Constructor(item, NULL);

  if(!node) return Fail;

  if(!Tree_isEmpty(self)) 
    return _Node_Insert(self->root, node, self->cmp);
  
  self->root = node;
  return Success;
}

/* Remove */
static task_t _Node_Sink(node_t * const self, CompareFunction cmp)
{
  if(!self->L && !self->R) {
    if(self->P->L == self) self->P->L = NULL;
    else                   self->P->R = NULL;
    return Success;
  }

  node_t * const far = self->L ? _Node_FarR(self->L) : _Node_FarL(self->R) ;

  self->item = far->item;

  return _Node_Remove(far, far->item, cmp);
}

static task_t _Node_Remove(node_t * const self, void * const item, CompareFunction cmp)
{
  switch (cmp(self->item, item)) {
    case -1: return _Node_Remove(self->L, item, cmp);
    case +1: return _Node_Remove(self->R, item, cmp);
    case  0: return _Node_Sink(self, cmp);
    default: return Fail;
  }
}

task_t Tree_Remove(tree_t * const self, void * const item)
{
  // ? Check if this tree contains item
  if(!Tree_isContain(self, item)) return Fail;

  // ? Make sure that is not root
  if(self->cmp(self->root->item, item))
    return _Node_Remove(self->root, item, self->cmp);
  
  // ? Make sure that root has leaves
  if(self->root->L || self->root->R) 
    return _Node_Sink(self->root, self->cmp);

  // ? The last case: is the root and the root does not have any leaves
  _Node_Destructor(self->root);
  self->root = NULL;

  return Success;
}

/* isEmpty */
bool_t Tree_isEmpty(tree_t const * const self)
{
  return self ? self->root == NULL : True ;
}

/* isContain */
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
  return _Node_isContain(self->root, item, self->cmp);
}

/* Height */
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

/* Size */
static size_t _Node_Size(node_t const * const self)
{
  return self ? _Node_Size(self->L) + _Node_Size(self->R) + 1 : 0 ; 
}

size_t Tree_Size(tree_t const * const self)
{
  return self ? _Node_Size(self->root) : 0 ;
}
