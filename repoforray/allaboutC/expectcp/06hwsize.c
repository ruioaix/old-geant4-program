#include <stdio.h>
int a[10];
int main(void) {
  int b[10];
  int i=0;
  printf("local:%x\n",&i);
  printf("global:%x\n",a);
  printf("global:%x\n",&a[1]);
  for(i=0;i<10;i++)
  {
    b[i]=i;
  }
  printf("hello world\n");
  return 0;
}

