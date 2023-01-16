#include "sort.h"
#include <stdlib.h>

static char * _MergeSort(char array[], size_t head, size_t tail, CompareFunction cmp)
{
  if( !(head + 1 < tail) ) return array;

  const size_t half = ( head + tail ) >> 1 ;

  _MergeSort(array, head, half, cmp);
  _MergeSort(array, half, tail, cmp);

  size_t i = head;
  size_t j = half;
  const size_t len = tail - head;

  char * const merge = (char*)calloc(len, sizeof(char));

  size_t curr = 0;

  while( i < half && j < tail )
    merge[curr++] = cmp(array[i], array[j]) == -1 ? array[i++] : array[j++] ;

  if     ( !(i < half) ) while( j < tail ) merge[curr++] = array[j++];
  else if( !(j < tail) ) while( i < half ) merge[curr++] = array[i++];

  for(curr = 0; curr < len; ++curr) array[head + curr] = merge[curr];

  free(merge);

  return array;
}

char * Sort(char array[], size_t len, CompareFunction cmp)
{
  return _MergeSort(array, 0, len, cmp);
}
