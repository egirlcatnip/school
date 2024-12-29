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

void heapify(int a[], int a_len, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < a_len && a[left] > a[largest]) {
    largest = left;
  }

  if (right < a_len && a[right] > a[largest]) {
    largest = right;
  }

  if (largest != i) {
    int tmp = a[i];
    a[i] = a[largest];
    a[largest] = tmp;

    heapify(a, a_len, largest);
  }
}

void heap_sort(int a[], int a_len) {
  for (int i = a_len / 2 - 1; i >= 0; i--) {
    heapify(a, a_len, i);
  }

  for (int i = a_len - 1; i > 0; i--) {
    int tmp = a[0];
    a[0] = a[i];
    a[i] = tmp;

    heapify(a, i, 0);
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  heap_sort(a, a_len);

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