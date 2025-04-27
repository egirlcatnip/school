#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void bubble_sort(int array[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void fill_array(int array[], int size) {
  for (int i = 0; i < size; i++) {
    int random = rand() % size;
    array[i] = random;
  }
}

int sequence_search(int array[], int size, int element, int *cycles) {
  *cycles = 0;
  for (int i = 0; i < size; i++) {
    (*cycles)++;
    if (array[i] == element) {
      return i;
    }
  }
  return -1;
}

int binary_search(int array[], int size, int element, int *cycles) {
  int left = 0, right = size - 1;
  *cycles = 0;
  while (left <= right) {
    (*cycles)++;
    int mid = left + (right - left) / 2;
    if (array[mid] == element)
      return mid;
    if (array[mid] < element)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

int interpolation_search(int array[], int size, int element, int *cycles) {
  int left = 0, right = size - 1;
  *cycles = 0;
  while (left <= right && element >= array[left] && element <= array[right]) {
    (*cycles)++;
    if (left == right) {
      if (array[left] == element)
        return left;
      return -1;
    }

    int pos = left + (((right - left) / (array[right] - array[left])) *
                      (element - array[left]));

    if (array[pos] == element)
      return pos;
    if (array[pos] < element)
      left = pos + 1;
    else
      right = pos - 1;
  }
  return -1;
}

int main(void) {
  // Random seed
  srand(time(NULL));

  int size = 50;
  int array[size];

  fill_array(array, size);
  printf("Random array:\n");
  print_array(array, size);
  bubble_sort(array, size);
  printf("Sorted array:\n");
  print_array(array, size);

  int search_element = rand() % size;

  int cycles, index;

  printf("\n");
  printf("Search element: %d\n", search_element);
  printf("Random array of size: %d\n", size);
  printf("\n");

  index = sequence_search(array, size, search_element, &cycles);

  if (index != -1)
    printf("Sequential search:\n  found at index %d (%d cycles)\n", index,
           cycles);
  else
    printf("Sequential search:\n  not found\n");

  index = binary_search(array, size, search_element, &cycles);
  if (index != -1)
    printf("Binary search:\n  found at index %d (%d cycles)\n", index, cycles);
  else
    printf("Sequential search:\n  not found\n");

  index = interpolation_search(array, size, search_element, &cycles);
  if (index != -1)
    printf("Interpolation search:\n  found at index %d (%d cycles)\n", index,
           cycles);
  else
    printf("Sequential search:\n  not found\n");

  return 0;
}

// Konya

// Expected output:

/*
Random array:
[48, 14, 31, 41, 24, 12, 44, 43, 19, 22, 24, 16, 17, 2, 13, 34, 4, 33, 12, 39,
40, 25, 34, 4, 16, 47, 48, 0, 5, 7, 35, 3, 22, 17, 46, 46, 29, 43, 42, 0, 17,
16, 19, 34, 20, 32, 18, 25, 17, 32] Sorted array: [0, 0, 2, 3, 4, 4, 5, 7, 12,
12, 13, 14, 16, 16, 16, 17, 17, 17, 17, 18, 19, 19, 20, 22, 22, 24, 24, 25, 25,
29, 31, 32, 32, 33, 34, 34, 34, 35, 39, 40, 41, 42, 43, 43, 44, 46, 46, 47, 48,
48]

Search element: 16
Random array of size: 50

Sequential search:
  found at index 12 (13 cycles)
Binary search:
  found at index 14 (4 cycles)
Interpolation search:
  found at index 12 (10 cycles)
*/
