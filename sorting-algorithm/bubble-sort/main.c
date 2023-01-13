#include "sort.h"
#include <stdio.h>
#include <string.h>

static char compare(char a, char b)
{
  return a == b ? 0 : ( a > b ? +1 : -1 ) ;
}

int main(void)
{
  char array[] = "9ZHwaq1h8kQAvcftKLWSXzGmi0rdxJ67Ne5BCEjnsYUFVg23Rby4MIDOPplouT";

  printf("before: %s\r\n", array);
  printf("after:  %s\r\n", Sort(array, strlen(array), compare));

  return 0;
}
