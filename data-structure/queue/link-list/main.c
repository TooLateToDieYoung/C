#include "queue.h"
#include <stdio.h>

int main(void)
{
  char data[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  queue_t * queue = Queue_Constructor();

  char * ptr = &data[0];
  while(*ptr) Queue_Push(queue, ptr++);
  while(Queue_Length(queue)) printf("%c, ", *(char*)Queue_Take(queue));
  printf("\r\n");

  return Queue_Destructor(queue);
}