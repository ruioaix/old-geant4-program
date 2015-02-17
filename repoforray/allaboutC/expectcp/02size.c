#include <stdio.h>
int main(void) {
  int b=3;
  int *p=&b;
  unsigned int a=sizeof(int)**p;
  printf("%d\n",a);
  return 0;
}

