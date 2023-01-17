#include <stdio.h>
#include "list.h"

static char compare(void const * const a, void const * const b)
{
  const char A = *(char*)a;
  const char B = *(char*)b;

  return A == B ? 0 : ( A > B ? -1 : +1 ) ;
}

int main(void)
{
  char upper[] = "XYCLHGFBTIJDEOPQRMNSAKZWUV";
  char lower[] = "aruvemtyzqjncdlfwxksbghopi";

  list_t * const list = List_Constructor();

  if(!list) return printf("constructor failed!\r\n");

  for(size_t i = 0; i < 26; ++i) 
  {
    List_PushHead(list, &upper[i]);
    List_PushTail(list, &lower[i]);
  }

  List_QuickSort(list, compare);

  char * head = 0;
  char * tail = 0;
  while( List_Length(list) )
  {
    head = List_TakeHead(list);
    tail = List_TakeTail(list);
    printf("(head, tail) = (%c, %c)\r\n", *head, *tail);
  }

  return List_Destructor(list);
}
