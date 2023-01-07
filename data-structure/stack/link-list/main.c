#include "stack.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
  const char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const size_t len = strlen(str);

  stack_t * const stack = Stack_Constructor();

  for(size_t i = 0; i < len; ++i) Stack_Push(stack, (void*)&str[i]);

  while( Stack_Length(stack) ) printf("%c, ", *(char*)Stack_Take(stack));

  printf("\r\n");

  return Stack_Destructor(stack);
}
