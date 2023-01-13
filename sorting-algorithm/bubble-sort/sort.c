#include "sort.h"

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  char temp;
  size_t i, j, k;
  
  for(i = 0; i < len; ++i) { 
    k = i;

    for(j = i + 1; j < len; ++j) 
      if( cmp(array[k], array[j]) == +1 ) k = j;

    temp = array[i];
    array[i] = array[k];
    array[k] = temp;
  }

  return array;
}
