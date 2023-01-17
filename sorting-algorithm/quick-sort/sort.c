#include "sort.h"

static void _Swap(char * const a, char * const b)
{
  char t = *a;
  *a = *b;
  *b =  t;
}

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  if(len < 2) return array;

  size_t h = 1;
  size_t t = len - 1;

  while( h != t + 1 ) {
    if( cmp(array[0], array[t]) == -1 ) --t;
    else _Swap(&array[h++], &array[t]);
  }

  if(t) _Swap(&array[0], &array[t]);

  Sort(&array[0],       t, cmp);
  Sort(&array[h], len - h, cmp);

  return array;
}
