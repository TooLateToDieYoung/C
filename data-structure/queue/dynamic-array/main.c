#include "queue.h"
#include <stdio.h>

int main(void)
{
  char data[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char * ptr = NULL;

  queue_t * queue = Queue_Constructor(50); // ? circular queue

  // ? 0 ~ 35
  ptr = &data[0];
  while(*ptr) Queue_Push(queue, ptr++);
  while(Queue_Length(queue)) printf("%c, ", *(char*)Queue_Take(queue));
  printf("\r\n");

  // ? 36 ~ 50 ~ 26
  ptr = &data[0];
  while(*ptr) Queue_Push(queue, ptr++);
  while(Queue_Length(queue)) printf("%c, ", *(char*)Queue_Take(queue));
  printf("\r\n");

  return Queue_Destructor(queue);
}