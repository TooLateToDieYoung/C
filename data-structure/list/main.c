#include <stdio.h>
#include "list.h"

int main(void)
{
  char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char lower[] = "abcdefghijklmnopqrstuvwxyz";

  list_t * const list = List_Constructor();

  if(!list) return printf("constructor failed!\r\n");

  for(size_t i = 0; i < 26; ++i) 
  {
    List_PushHead(list, &upper[i]);
    List_PushTail(list, &lower[i]);
  }

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
