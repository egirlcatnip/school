#include <stdio.h>

int int_to_bin(int num) {
  int binary = 0;
  int base = 1;
  int temp = num;

  while (temp > 0) {
    int last_digit = temp % 2;
    binary = binary + last_digit * base;
    base = base * 10;
    temp = temp / 2;
  }

  return binary;
}

void print_encoded(int bin) {
  int value = 0;
  while (bin > 0) {
    int digit = bin % 10;
    if (digit == 1) {
      printf("%i ", value);
    }
    value++;
    bin = bin / 10;
  }
}

int _log2(int n) {
  int count = 0;
  while (n) {
    n /= 2;
    count++;
  }
  return count;
}

void print_table(int size) {
  printf("index\t");
  printf(" | ");
  printf("bin     ");
  printf(" | ");
  printf("val");
  printf("\n");

  for (int i = 0; i <= size; i++) {
    int bin = int_to_bin(i);

    printf("%i\t", i);
    printf(" | ");
    printf("%0*d", 8, bin);
    printf(" | ");
    print_encoded(bin);

    printf("\n");
  }
}

int main(void) {
  // This is only part of the finished hw2
  print_table(15);

  return 0;
}

// Konya

// Expected output
/*
index    | bin      | val
0        | 00000000 |
1        | 00000001 | 0
2        | 00000010 | 1
3        | 00000011 | 0 1
4        | 00000100 | 2
5        | 00000101 | 0 2
6        | 00000110 | 1 2
7        | 00000111 | 0 1 2
8        | 00001000 | 3
9        | 00001001 | 0 3
10       | 00001010 | 1 3
11       | 00001011 | 0 1 3
12       | 00001100 | 2 3
13       | 00001101 | 0 2 3
14       | 00001110 | 1 2 3
15       | 00001111 | 0 1 2 3
*/
