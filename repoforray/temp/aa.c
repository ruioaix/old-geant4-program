#include <stdio.h>
int a=1,b=2;
int x=11;

void print_time (void) {
  printf("%d,%d\n",a,b);
}

int main(void) {
  int a=222,b=333;
  print_time();
  print_time();
  return 0;
}
