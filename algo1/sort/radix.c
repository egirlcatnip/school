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

int get_max(int a[], int a_len) {
  int max = a[0];
  for (int i = 1; i < a_len; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }
  return max;
}

void counting_sort_for_radix(int a[], int a_len, int exp) {
  int output[a_len];
  int count[10] = {0};

  for (int i = 0; i < a_len; i++) {
    count[(a[i] / exp) % 10]++;
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = a_len - 1; i >= 0; i--) {
    output[count[(a[i] / exp) % 10] - 1] = a[i];
    count[(a[i] / exp) % 10]--;
  }

  for (int i = 0; i < a_len; i++) {
    a[i] = output[i];
  }
}

void radix_sort(int a[], int a_len) {
  int max = get_max(a, a_len);

  for (int exp = 1; max / exp > 0; exp *= 10) {
    counting_sort_for_radix(a, a_len, exp);
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  radix_sort(a, a_len);

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