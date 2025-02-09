#include <assert.h>
#include <stdio.h>

void print_array(int a[], int a_len) {
  printf("[");
  for (int i = 0; i < a_len; i++) {
    if (a[i] != 0) {
      printf("%i", a[i]);

      if (i < a_len - 1) {
        printf(", ");
      }
    }
  }
  printf("]");
}

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
  int base = 1;
  while (bin > 0) {
    int digit = bin % 10;
    if (digit == 1) {
      printf("%d ", value);
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

  int space = _log2(size);
  // space = space > 7 ? space : 7;

  printf("index");
  // printf("%*c", space, ' ');
  printf(" | ");
  printf(" bin ");
  printf(" | ");
  printf("val");
  printf("\n");

  for (int i = 0; i <= size; i++) {
    int bin = int_to_bin(i);

    printf("%*i", space, i);
    printf(" | ");
    printf("%0*d", space, bin);
    printf(" | ");

    print_encoded(bin);

    printf("\n");
  }
}

int main(void) {
  print_table(31);

  return 0;
}

// Konya

// Expected output
/*
index | bin  | val
 0    | 000  |
 1    | 001  | 0
 2    | 010  | 1
 3    | 011  | 0 1
 4    | 100  | 2
 5    | 101  | 0 2
 6    | 110  | 1 2
 7    | 111  | 0 1 2


*/