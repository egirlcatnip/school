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

void sort_array(int a[], int a_len) {
  for (int i = 0; i < a_len - 1; i++) {
    for (int j = 0; j < a_len - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        int tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }
  }
}

int rand_partition(int a[], int p, int r) {
  int pivot = a[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (a[j] <= pivot) {
      i++;
      int temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
  }
  int temp = a[i + 1];
  a[i + 1] = a[r];
  a[r] = temp;
  return i + 1;
}

int rand_select(int a[], int p, int r, int i) {
  if (p == r) {
    return a[p];
  }
  int q = rand_partition(a, p, r);
  int k = q - p;
  if (i == k) {
    return a[q];
  } else if (i < k) {
    return rand_select(a, p, q - 1, i);
  } else {
    return rand_select(a, q + 1, r, i - k - 1);
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  int index = 3;

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  int selection = rand_select(a, 0, a_len - 1, index);

  printf("Selected %d (a[%d])\n", selection, index);
  sort_array(a, a_len);

  printf("\n");
  printf("Sorted array:\n");
  print_array(a, a_len);

  return 0;
}
// Konya

// Expected output
/*
Unsorted array:
[0, 5, 4, 3, 2, 1, 0, 6, 0]

Sorted array:
[0, 0, 0, 1, 2, 3, 4, 5, 6]

Selected 6 (a[8])
*/
