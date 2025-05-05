#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void fill_array(float *arr, unsigned size) {
  for (unsigned i = 0; i < size; i++) {
    arr[i] = (float)i;
  }
}

void run_size(unsigned size) {
  matrix *m1 = matrix_create(size, size);
  matrix *m2 = matrix_create(size, size);

  // Dynamically allocate memory for arrays
  float *arr1 = (float *)malloc(size * size * sizeof(float));
  if (!arr1) {
    printf("Memory allocation failed for arr1\n");
    return;
  }

  float *arr2 = (float *)malloc(size * size * sizeof(float));
  if (!arr2) {
    printf("Memory allocation failed for arr2\n");
    free(arr1);
    return;
  }

  fill_array(arr1, size * size);
  fill_array(arr2, size * size);

  unsigned size1 = size * size;
  unsigned size2 = size * size;

  matrix_set_fromarray(m1, arr1, size1);
  matrix_set_fromarray(m2, arr2, size2);

  // Add two matrixes
  matrix *m3 = matrix_add(m1, m2);
  printf("\nMatrix 1 + Matrix 2\n");

  // Multiply two matrixes
  printf("Matrix 1 * Matrix 2\n");
  matrix *m4 = matrix_multiply(m1, m2);

  printf("\n");

  // Square root of a matrix
  printf("Square root of Matrix 1\n");
  matrix *m5 = matrix_sqrt(m1);

  // Free matrixes
  matrix_free(m1);
  matrix_free(m2);
  matrix_free(m3);
  matrix_free(m4);
  matrix_free(m5);

  // Free dynamically allocated arrays
  free(arr1);
  free(arr2);
}

void run_small(void) {
  matrix *m1 = matrix_create(5, 5);
  matrix *m2 = matrix_create(5, 5);

  float arr1[] = {
      00.0, 01.0, 02.0, 03.0, 04.0, //
      10.0, 11.0, 12.0, 13.0, 14.0, //
      21.0, 22.0, 23.0, 24.0, 25.0, //
      30.0, 31.0, 32.0, 33.0, 34.0, //
      40.0, 41.0, 42.0, 43.0, 44.0, //
  };

  float arr2[] = {
      99.0, 98.0, 97.0, 96.0, 95.0, //
      89.0, 88.0, 87.0, 86.0, 85.0, //
      79.0, 78.0, 77.0, 76.0, 75.0, //
      69.0, 68.0, 67.0, 66.0, 65.0, //
      59.0, 58.0, 57.0, 56.0, 55.0, //
  };

  unsigned size1 = sizeof(arr1) / sizeof(arr1[0]);
  unsigned size2 = sizeof(arr2) / sizeof(arr2[0]);

  matrix_set_fromarray(m1, arr1, size1);
  matrix_set_fromarray(m2, arr2, size2);

  printf("Matrix 1:\n");
  matrix_print(m1);

  printf("\n");

  printf("Matrix 2:\n");
  matrix_print(m2);

  // Add two matrixes
  matrix *m3 = matrix_add(m1, m2);
  printf("\nMatrix 1 + Matrix 2:\n");
  matrix_print(m3);

  printf("\n");

  // Multiply two matrixes
  printf("Matrix 1 * Matrix 2:\n");
  matrix *m4 = matrix_multiply(m1, m2);
  matrix_print(m4);

  printf("\n");

  // Square root of a matrix
  printf("Square root of Matrix 1:\n");
  matrix *m5 = matrix_sqrt(m1);
  matrix_print(m5);

  // Free matrixes
  matrix_free(m1);
  matrix_free(m2);
  matrix_free(m3);
  matrix_free(m4);
  matrix_free(m5);
}

int main(void) {
  run_small();

  // Uncomment for a big test
  // run_size(1000);

  return 0;
}

// Konya

// Expected output:

/*
00000.00 00001.00 00002.00 00003.00 00004.00
00010.00 00011.00 00012.00 00013.00 00014.00
00021.00 00022.00 00023.00 00024.00 00025.00
00030.00 00031.00 00032.00 00033.00 00034.00
00040.00 00041.00 00042.00 00043.00 00044.00

Matrix 2:
00099.00 00098.00 00097.00 00096.00 00095.00
00089.00 00088.00 00087.00 00086.00 00085.00
00079.00 00078.00 00077.00 00076.00 00075.00
00069.00 00068.00 00067.00 00066.00 00065.00
00059.00 00058.00 00057.00 00056.00 00055.00

Matrix 1 + Matrix 2:
00099.00 00099.00 00099.00 00099.00 00099.00
00099.00 00099.00 00099.00 00099.00 00099.00
00100.00 00100.00 00100.00 00100.00 00100.00
00099.00 00099.00 00099.00 00099.00 00099.00
00099.00 00099.00 00099.00 00099.00 00099.00

Matrix 1 * Matrix 2:
00690.00 00680.00 00670.00 00660.00 00650.00
04640.00 04580.00 04520.00 04460.00 04400.00
08985.00 08870.00 08755.00 08640.00 08525.00
12540.00 12380.00 12220.00 12060.00 11900.00
16490.00 16280.00 16070.00 15860.00 15650.00

Square root of Matrix 1:
00000.00 00001.00 00001.41 00001.73 00002.00
00003.16 00003.32 00003.46 00003.61 00003.74
00004.58 00004.69 00004.80 00004.90 00005.00
00005.48 00005.57 00005.66 00005.74 00005.83
00006.32 00006.40 00006.48 00006.56 00006.63
*/
