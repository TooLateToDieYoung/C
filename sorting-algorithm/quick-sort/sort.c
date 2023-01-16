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

  const char index = array[0];

  size_t c = 1;
  size_t h = 0;
  size_t t = len - 1;

  while( h < t ) {
    switch (cmp(index, array[c])) {
      case -1: _Swap(&array[t--], &array[c]);   continue;
      case +1: _Swap(&array[h++], &array[c++]); continue;
      default: continue;
    }
  }

  Sort(&array[0],       c, cmp);
  Sort(&array[c], len - c, cmp);

  return array;
}
