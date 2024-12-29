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

void counting_sort(int a[], int b[], int k, int a_len) {
  int c[k + 1];

  for (int i = 0; i <= k; i++) {
    c[i] = 0;
  }

  for (int i = 0; i < a_len; i++) {
    c[a[i]]++;
  }

  for (int i = 1; i <= k; i++) {
    c[i] += c[i - 1];
  }

  for (int i = a_len - 1; i >= 0; i--) {
    b[c[a[i]] - 1] = a[i];
    c[a[i]]--;
  }

  for (int i = 0; i < a_len; i++) {
    a[i] = b[i];
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  int b[a_len];
  int k;

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  counting_sort(a, b, k, a_len);

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