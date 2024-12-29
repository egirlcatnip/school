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

void selection_sort(int a[], int a_len) {
  for (int j = 0; j <= a_len - 2; j++) {
    int min = j;
    for (int i = j + 1; i < a_len; i++) {
      if (a[i] < a[min]) {
        min = i;
      }
    }

    int tmp = a[j];
    a[j] = a[min];
    a[min] = tmp;
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  selection_sort(a, a_len);

  printf("Sorted array:\n");
  print_array(a, a_len);
  printf("\n");
}

// Konya

// Expected output
/*
Unsorted array:
[0, 5, 4, 3, 2, 1, 0, 6, 0]

Sorted array:
[0, 0, 0, 1, 2, 3, 4, 5, 6]
*/