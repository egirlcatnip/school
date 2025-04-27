#include <stdio.h>

void _swap(int a[], int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

int _quick_sort_partition(int a[], int p, int r) {
  int pivot = a[r];
  int i = p - 1;

  for (int j = p; j <= r - 1; j++) { // Loop through to r-1
    if (a[j] <= pivot) {
      i++;
      _swap(a, i, j);
    }
  }

  _swap(a, i + 1, r); // Place pivot in correct position
  return i + 1;
}

void quick_sort(int a[], int p, int r) {
  if (p < r) {
    int q = _quick_sort_partition(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
  }
}

void print_array(int a[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main() {
  int arr[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Unsorted array:\n");
  print_array(arr, n);

  quick_sort(arr, 0, n - 1);

  printf("Sorted array:\n");
  print_array(arr, n);

  return 0;
}
