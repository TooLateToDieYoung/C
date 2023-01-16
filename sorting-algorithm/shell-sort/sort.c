#include "sort.h"

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  for(size_t gap = len >> 1; gap; gap >>= 1)
  {
    for(size_t shell = gap; shell < len; ++shell)
    {
      size_t curr = shell;
      char temp = array[curr];
      for(;
        curr >= gap && cmp(temp, array[curr - gap]) == -1; 
        curr -= gap
      ) array[curr] = array[curr - gap];
      array[curr] = temp;
    }
  }

  return array;
}
