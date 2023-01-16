#include "hash.h"
#include <stdio.h>
#include <string.h>

#define LENGTH 10

static size_t function(char const * const key, size_t len)
{
  size_t order = 0;

  for(size_t i = 0; i < len; ++i) {
    order += key[i];
    order <<= 1;
  }

  return order % LENGTH;
}

static char array[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char * const keys[26] = {
  [0] = "hash-table",
  [1] = "stone",
  [2] = "queue",
  [3] = "stack",
  [4] = "tree",
  [5] = "set",
  [6] = "map",
  [7] = "data-structure",
  [8] = "dynamic-array",
  [9] = "link-list",
  [10] = "hash-table-1",
  [11] = "stone-1",
  [12] = "queue-1",
  [13] = "stack-1",
  [14] = "tree-1",
  [15] = "set-1",
  [16] = "map-1",
  [17] = "data-structure-1",
  [18] = "dynamic-array-1",
  [19] = "link-list-1",
  [20] = "hash-table-2",
  [21] = "stone-2",
  [22] = "queue-2",
  [23] = "stack-2",
  [24] = "tree-2",
  [25] = "set-2"
};

int main(void)
{
  hash_t * const hash = Hash_Constructor(LENGTH, function);

  for(size_t i = 0; i < 26; ++i)
    Hash_Insert(hash, keys[i], strlen(keys[i]), &array[i]);

  printf("key: %s -> value: %c\r\n", keys[5], *(char*)Hash_Delete(hash, keys[5], strlen(keys[5])));
  printf("key: %s -> value: %c\r\n", keys[9], *(char*)Hash_Delete(hash, keys[9], strlen(keys[9])));

  return Hash_Destructor(hash);
}