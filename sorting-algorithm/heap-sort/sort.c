#include "sort.h"
#include <stdlib.h>

#define _P(curr) ( (curr) >> 1 )
#define _L(curr) ( (curr) << 1 | 0 )
#define _R(curr) ( (curr) << 1 | 1 )

static char temp = 0;

static void _PushHeapify(char heap[], size_t curr, CompareFunction cmp)
{
  if(!_P(curr)) return;

  if(cmp(heap[_P(curr)], heap[curr]) != +1) return;

  temp = heap[_P(curr)];
  heap[_P(curr)] = heap[curr];
  heap[curr] = temp;

  return _PushHeapify(heap, _P(curr), cmp);
}

static void _TakeHeapify(char heap[], size_t curr, size_t last, CompareFunction cmp)
{
  size_t index = curr;

  if( _L(curr) < last && cmp(heap[index], heap[_L(curr)]) == +1 ) index = _L(curr);
  if( _R(curr) < last && cmp(heap[index], heap[_R(curr)]) == +1 ) index = _R(curr);

  if(index == curr) return;

  temp = heap[curr];
  heap[curr] = heap[index];
  heap[index] = temp;
  
  return _TakeHeapify(heap, index, last, cmp);
}

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  char * const heap = (char*)calloc(len + 1, sizeof(char));

  if(!heap) return array;

  for(size_t i = 0; i < len; ++i) {
    heap[i + 1] = array[i];
    _PushHeapify(heap, i + 1, cmp);
  }

  for(size_t i = 0; i < len; ++i) {
    array[i] = heap[1];
    heap[1]  = heap[len - i];
    _TakeHeapify(heap, 1, len - i - 1, cmp);
  }

  free(heap);
  
  return array;
}
