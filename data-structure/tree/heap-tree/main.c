#include "tree.h"
#include <stdio.h>
#include <string.h>

static char compare(void const * const a, void const * const b)
{
  const char A = *(char*)a;
  const char B = *(char*)b;

  return ( A == B ) ? ( 0 ) : ( ( A > B ) ? ( +1 ) : ( -1 ) ) ; // ? min heap
//return ( A == B ) ? ( 0 ) : ( ( A < B ) ? ( +1 ) : ( -1 ) ) ; // ? max heap
}

int main(void)
{
  char data[] = "QWERT5XCV7UIOPA6HJYSNM01LZ82DFGB34K9";
  const size_t len = strlen(data);
  size_t i = 0;
  tree_t * const heap = Tree_Constructor(compare, len);

  while(!Tree_isFull(heap)) Tree_Push(heap, &data[i++]);
  while(!Tree_isEmpty(heap)) printf("%c, ", *(char*)Tree_Take(heap));
  printf("\r\n");

  return Tree_Destructor(heap);
}
