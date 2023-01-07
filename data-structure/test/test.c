#include "test.h"
#include <stdlib.h>

char TEST_RandomChar()
{
  return random() % 26 + 'A';
}
