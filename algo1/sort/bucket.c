#include <stdio.h>
#include <stdlib.h>

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

void insertion_sort(int a[], int a_len) {
  for (int i = 1; i < a_len; i++) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = key;
  }
}

void bucket_sort(int a[], int a_len) {
  int max = a[0];
  for (int i = 1; i < a_len; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  int bucket_count = max + 1;
  int *buckets[bucket_count];

  for (int i = 0; i < bucket_count; i++) {
    buckets[i] = (int *)malloc(a_len * sizeof(int));
    for (int j = 0; j < a_len; j++) {
      buckets[i][j] = 0;
    }
  }

  int bucket_sizes[bucket_count];
  for (int i = 0; i < bucket_count; i++) {
    bucket_sizes[i] = 0;
  }

  for (int i = 0; i < a_len; i++) {
    int bucket_index = a[i];
    buckets[bucket_index][bucket_sizes[bucket_index]] = a[i];
    bucket_sizes[bucket_index]++;
  }

  int index = 0;
  for (int i = 0; i < bucket_count; i++) {
    insertion_sort(buckets[i], bucket_sizes[i]);
    for (int j = 0; j < bucket_sizes[i]; j++) {
      a[index++] = buckets[i][j];
    }
  }

  for (int i = 0; i < bucket_count; i++) {
    free(buckets[i]);
  }
}

int main(void) {
  int a[] = {0, 5, 4, 3, 2, 1, 0, 6, 0};
  int a_len = sizeof(a) / sizeof(a[0]);

  printf("Unsorted array:\n");
  print_array(a, a_len);
  printf("\n");

  bucket_sort(a, a_len);

  printf("Sorted array:\n");
  print_array(a, a_len);
  printf("\n");
}