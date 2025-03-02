#include <stdio.h>

int main(void) {
  printf("test");

  return 0;
}

/*
cc -g0 -O3 -S ./example.c -o ./example.s;
cc ./example.s -o ./example.exe; ./example.exe;
*/
