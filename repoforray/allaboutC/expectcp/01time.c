#include <stdio.h>
#include <time.h>

int main(void) {
  time_t biggest=0x7fffff;;
  printf("%d\n",sizeof(biggest));
  printf("biggest=%s\n",ctime(&biggest));
  printf("biggest=%s\n",asctime(gmtime(&biggest)));
  time();
  return 0;
}

