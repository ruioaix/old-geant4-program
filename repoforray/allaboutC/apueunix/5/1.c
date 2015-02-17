#include <stdio.h>
int main() {
  FILE *a=fopen("123","a+");
  if(!a) {
    printf("cant open 123\n");
    return 0;
  }
  char b[10];
  while(fgets(b,11,a)) {
    printf("%s\n",b);
  }
  char c='a';
  int d='a';
  if(!putc(d,a)) {
    printf("cnat put in");
    return 0;
  }


  printf("over\n");
  return 0;
}
  



