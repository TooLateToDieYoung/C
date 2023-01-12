#include "tree.h"
#include <stdio.h>
#include <string.h>

static char compare(void const * const a, void const * const b)
{
  const char A = *(char*)a;
  const char B = *(char*)b;

  return ( A == B ) ? ( 0 ) : ( ( A > B ) ? ( -1 ) : ( +1 ) ) ;
}

int main(void)
{
  char data[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const size_t len = strlen(data);

  tree_t * const tree = Tree_Constructor(compare);

  for(size_t i = 0; i < len; ++i) Tree_Insert(tree, &data[i]);

  printf("Before ->  Height: %2ld, Size: %2ld\r\n", Tree_Height(tree), Tree_Size(tree));
  
  for(size_t i = 0; !Tree_isEmpty(tree); ++i) {
    Tree_Remove(tree, &data[i]);
    printf("Remove: %c, Height: %2ld, Size: %2ld\r\n", data[i], Tree_Height(tree), Tree_Size(tree));
  }

  return Tree_Destructor(tree);
}
