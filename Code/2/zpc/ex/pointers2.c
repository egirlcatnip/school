#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int *a, int a_len) {
  printf("[");
  for (int i = 0; i < a_len; i++) {
    printf("%i", a[i]);
    if (i < a_len - 1) {
      printf(", ");
    }
  }
  printf("]");
  printf("\n");
}

typedef struct stuff {
  int i;
  char c;
  int *p;
  double d;

} stuff;

int main(void) {
  stuff s = {};

  printf("Structure stuff:\n");

  printf("whole struct:\n");
  printf("ptr: %p  | size: %zi bytes \n", &s, sizeof(s));

  printf("\n");

  printf("s int:\n");
  printf("ptr: %p  | size: %zi bytes \n", &s.i, sizeof(s.i));

  printf("\n");

  printf("s char:\n");
  printf("ptr: %p  | size: %zi bytes \n", &s.c, sizeof(s.c));

  printf("\n");

  printf("s int *:\n");
  printf("ptr: %p  | size: %zi bytes \n", &s.p, sizeof(s.p));

  printf("\n");

  printf("s double:\n");
  printf("ptr: %p  | size: %zi bytes \n", &s.d, sizeof(s.d));

  printf("\n");

  printf("Difference of ptr location between s.i and s.c:\n");
  printf("s.i: %p\n", &s.i);
  printf("and\n");
  printf("s.c: %p\n", &s.c);

  long long diff = llabs((char *)&s.c - (char *)&s.i);

  printf("Difference:  %zi bytes\n", diff);

  printf("Size of s.i: %zi bytes\n", sizeof(s.i));

  return 0;
}

// Konya

// Expected output:

/*
Structure stuff:
whole struct:
ptr: 0000000A1D32F708  | size: 24 bytes

s int:
ptr: 0000000A1D32F708  | size: 4 bytes

s char:
ptr: 0000000A1D32F70C  | size: 1 bytes

s int *:
ptr: 0000000A1D32F710  | size: 8 bytes

s double:
ptr: 0000000A1D32F718  | size: 8 bytes

Difference of ptr location between s.i and s.c:
s.i: 0000000A1D32F708
and
s.c: 0000000A1D32F70C
Difference:  4 bytes
Size of s.i: 4 bytes
*/
