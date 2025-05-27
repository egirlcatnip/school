#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void mem_cpy(void *dest, void *src, size_t count) {
  unsigned char *d = (unsigned char *)dest;
  unsigned char *s = (unsigned char *)src;
  for (size_t i = 0; i < count; i++) {
    d[i] = s[i];
  }
}

int mem_cmp(void *lhs, void *rhs, size_t count) {
  unsigned char *l = (unsigned char *)lhs;
  unsigned char *r = (unsigned char *)rhs;

  for (size_t i = 0; i < count; i++) {
    if (l[i] != r[i]) {
      if (l[i] > r[i]) {
        return 1;
      } else {
        return -1;
      }
    }
  }
  return 0;
}

void mem_set(void *dest, unsigned char value, size_t count) {
  unsigned char *d = (unsigned char *)dest;
  for (size_t i = 0; i < count; i++) {
    d[i] = value;
  }
}

void print_binary(int num, size_t size) {
  for (int i = size * 8 - 1; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
  printf("\n");
}

int main() {
  int num1 = 0b00100;
  int num2 = 0b00101;

  int size = sizeof(num1); // 4 bytes

  printf("num1: %d\n", num1);
  printf("num2: %d\n", num2);

  int result_mine = mem_cmp(&num1, &num2, size);
  int result_expected = memcmp(&num1, &num2, size);

  printf("Result mine: %d\n", result_mine);
  printf("Result expected: %d\n", result_expected);

  printf("Result mine: %d\n", result_mine);

  return 0;
}
