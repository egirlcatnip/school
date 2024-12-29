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

void _swap(int a[], int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

int _quick_sort_partition(int a[], int p, int r) {
  int pivot = a[r];
  int i = p - 1;

  for (int j = p; j < r; j++) {
    if (a[j] <= pivot) {
      i++;
      _swap(a, i, j);
    }
  }

  _swap(a, i + 1, r);
  return i + 1;
}

void quick_sort(int a[], int p, int r) {
  if (p < r) {
    int q = _quick_sort_partition(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
  }
}

int main() {
#define INIT_VALUES {0, 5, 4, 3, 2, 1, 0, 6, 0}

  int array[] = INIT_VALUES;

  int len = sizeof(array) / sizeof(array[0]);

  printf("Unsorted array:\n");
  print_array(array, len);
  printf("\n");

  quick_sort(array, 0, len - 1);

  printf("Sorted array:\n");
  print_array(array, len);
  printf("\n");

  return 0;
}

// Konya

// Expected output
/*
Unsorted array:
[0, 5, 4, 3, 2, 1, 0, 6, 0]

Sorted array:
[0, 0, 0, 1, 2, 3, 4, 5, 6]
*/