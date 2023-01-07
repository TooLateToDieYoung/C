#include <stdio.h>
#include "test.h"

int main(void)
{
  char temp = 0;

  do {
    printf("temp = %c\r\n", TEST_RandomChar());
  } while(scanf(" %c", &temp) && temp != 'q');

  return 0;
}
