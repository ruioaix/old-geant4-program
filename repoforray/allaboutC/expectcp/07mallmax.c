#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int MB=0;
  while (malloc(1<<20))
    ++MB;
  printf("%d MB\n",MB);
  return 0;
}

