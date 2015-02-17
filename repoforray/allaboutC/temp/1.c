#include <limits.h>
#include <stdio.h>
int 
main (void) {
  int unsigned a;
  a=1;
  printf("%d\n",a);

  printf("%s\n",CHAR_MIN<0?"SIGNED":"UNSIGNED");
  printf("%d\n",CHAR_MIN);
  printf("%d\n",CHAR_MAX);
  printf("%d\n",INT_MIN);




  
  return 0;
}

