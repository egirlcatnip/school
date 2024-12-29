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

void cocktail_sort(int a[], int a_len) {
  int left = 0;
  int right = a_len - 1;

  while (left < right) {
    for (int i = left; i < right; i++) {
      if (a[i] > a[i + 1]) {
        int tmp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = tmp;
      }
    }
    right--;

    for (int i = right; i > left; i--) {
      if (a[i] < a[i - 1]) {
        int tmp = a[i];
        a[i] = a[i - 1];
        a[i - 1] = tmp;
      }
    }
    left++;
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  cocktail_sort(a, a_len);

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