#include <stdio.h>
int main (void) {
  int i=0,j=0,k=0;
  +i||++j||++k;
  printf("%d,%d,%d",i,j,k);
  printf("\n%d\n",EOF);
  return 0;
}

