#include <stdio.h>

void print_array(int a[], int a_len) {
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

void array_insert(int *array, int length, int value) {
  for (int i = 0; i < length; i++) {
    if (array[i] == 0 || value < array[i]) {
      for (int j = length - 1; j > i; j--) {
        array[j] = array[j - 1];
      }
      array[i] = value;
      break;
    }
  }
}

int main(void) {
  int a[10] = {1, 2, 5, 7};
  print_array(a, 10);

  array_insert(a, 10, 11); // 2, 4, 6, 8, 10, 11
  print_array(a, 10);

  array_insert(a, 10, 11); // 2, 4, 6, 8, 10, 11
  print_array(a, 10);
}
