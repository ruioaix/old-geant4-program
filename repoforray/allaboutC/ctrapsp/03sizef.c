#include <stdio.h>
int main(void) {
  int i;
  i=sizeof(int);
  printf("int:%d\n",i);
  i=sizeof(char);
  printf("char:%d\n",i);
  i=sizeof(short);
  printf("short:%d\n",i);
  i=sizeof(long);
  printf("long:%d\n",i);
  i=sizeof(unsigned int);
  printf("unsigned int:%d\n",i);
  i=sizeof(float);
  printf("float:%d\n",i);
  i=sizeof(double);
  printf("double:%d\n",i);
  return 0;
}

