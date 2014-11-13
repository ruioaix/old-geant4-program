#include <stdio.h>

void newdef(char,short,float);

int main(void) {
  union {
    int i;
    char a;
    short b;
  } u;

  u.i=33;
  char aa=33;
  short bb=11;
  float cc=12;

  union {
    float c;
    double d;
  } ud;

  ud.d=12;
  //newdef(aa,bb,cc);
  newdef(u.a,u.b,ud.c);
}

