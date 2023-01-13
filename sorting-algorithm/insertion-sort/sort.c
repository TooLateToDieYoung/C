#include "sort.h"

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  char temp;
  size_t i, j;
  
  for(i = 1; i < len; ++i) {
    for(j = i; j && cmp(array[j - 1], array[j]) == +1; --j) {
      temp = array[j];
      array[j] = array[j - 1];
      array[j - 1] = temp;
    }
  }

  return array;
}
