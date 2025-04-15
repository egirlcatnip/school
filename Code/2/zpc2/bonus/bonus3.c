#include <stddef.h>
#include <stdio.h>

typedef unsigned char byte;

enum {
  BIGGER = 1,
  EQUAL = 0,
  SMALLER = -1,
};

typedef struct fraction {
  int numerator;
  size_t denominator;
} fraction;

typedef int compare_fn(void *, void *);

int compare_fraction(void *a, void *b) {
  fraction *fa = (fraction *)a;
  fraction *fb = (fraction *)b;

  // Trick for comparing fractions without floating-point arithmetic
  // a/b < c/d if a*d < b*c
  long long left = (long long)fa->numerator * fb->denominator;
  long long right = (long long)fb->numerator * fa->denominator;

  if (left < right)
    return SMALLER;
  if (left > right)
    return BIGGER;

  return EQUAL;
}

int compare_unsigned(void *a, void *b) {
  unsigned int *ua = (unsigned int *)a;
  unsigned int *ub = (unsigned int *)b;

  if (*ua < *ub)
    return SMALLER;
  if (*ua > *ub)
    return BIGGER;

  return EQUAL;
}

void swap(byte *a, byte *b) {
  byte temp = *a;
  *a = *b;
  *b = temp;
}

void generic_sort(void *array, size_t len, size_t elem_size, compare_fn *cmp) {
  byte *arr = (byte *)array; // Treat array as a byte array

  if (len == 0 || elem_size == 0) {
    return; // Nothing to sort
  }

  // Bubble sort
  for (size_t i = 0; i < len - 1; i++) {
    for (size_t j = 0; j < len - i - 1; j++) {

      byte *a = arr + j * elem_size;       // Pointer to the j-th element
      byte *b = arr + (j + 1) * elem_size; // Pointer to the (j+1)-th element

      int comparison = cmp(a, b);
      if (comparison == SMALLER) {
        for (size_t k = 0; k < elem_size; k++) {
          swap(a + k, b + k);
        }
      }
    }
  }
}

void fractions_sort(fraction *array, size_t len) {
  generic_sort(array, len, sizeof(fraction), compare_fraction);
}

void unsigned_sort(unsigned int *array, size_t len) {
  generic_sort(array, len, sizeof(unsigned int), compare_unsigned);
}

void print_fractions(fraction *array, size_t len) {
  printf("[");
  for (size_t i = 0; i < len; i++) {
    printf("%d/%zu", array[i].numerator, array[i].denominator);
    if (i < len - 1) {
      printf(", ");
    }
  }

  printf("]");
  printf("\n");
}

void print_unsigned_array(unsigned int *array, size_t len) {
  printf("[");
  for (size_t i = 0; i < len; i++) {
    printf("%u", array[i]);
    if (i < len - 1) {
      printf(", ");
    }
  }

  printf("]");
  printf("\n");
}

int main(void) {
  fraction fractions[] = {{1, 3}, {2, 5}, {3, 4}, {1, 2}, {5, 6}};
  unsigned int numbers[] = {42, 3, 19, 7, 100};

  size_t f_len = sizeof(fractions) / sizeof(fraction);
  size_t n_len = sizeof(numbers) / sizeof(unsigned int);

  printf("Unsorted fractions:\n");
  print_fractions(fractions, f_len);

  printf("\n");

  fractions_sort(fractions, f_len);
  printf("Sorted fractions:\n");
  print_fractions(fractions, f_len);

  printf("\n");

  printf("Unsorted unsigned integers:\n");
  print_unsigned_array(numbers, n_len);

  printf("\n");

  unsigned_sort(numbers, n_len);

  printf("Sorted unsigned integers:\n");
  print_unsigned_array(numbers, n_len);

  return 0;
}

// Konya

// Expected output:
/*
Unsorted fractions:
[1/3, 2/5, 3/4, 1/2, 5/6]

Sorted fractions:
[5/6, 3/4, 1/2, 2/5, 1/3]

Unsorted unsigned integers:
[42, 3, 19, 7, 100]

Sorted unsigned integers:
[100, 42, 19, 7, 3]
*/
