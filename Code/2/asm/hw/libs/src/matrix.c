#include "matrix.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

matrix *matrix_create(unsigned row, unsigned col) {
  matrix *m = (matrix *)malloc(sizeof(matrix));

  if (!m) {
    printf("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  m->data = (float *)calloc(row * col, sizeof(float));
  m->row = row;
  m->col = col;

  return m;
}

inline void matrix_free(matrix *m) {
  free(m->data);
  free(m);
}

inline float matrix_get(matrix *m, unsigned row, unsigned col) {
  assert(row < m->row && col < m->col);
  return m->data[row * m->col + col];
}

inline void matrix_set(matrix *m, unsigned row, unsigned col, float val) {
  assert(row < m->row && col < m->col);
  m->data[row * m->col + col] = val;
}

inline matrix *matrix_set_fromarray(matrix *m, float *array, unsigned size) {
  assert(size == m->row * m->col);

  for (unsigned i = 0; i < m->row; i++) {
    for (unsigned j = 0; j < m->col; j++) {
      matrix_set(m, i, j, array[i * m->col + j]);
    }
  }

  return m;
}

inline matrix *matrix_add(matrix *m1, matrix *m2) {
  assert(m1->row == m2->row && m1->col == m2->col);

  matrix *result = matrix_create(m1->row, m1->col);

  for (unsigned i = 0; i < m1->row; i++) {
    for (unsigned j = 0; j < m1->col; j++) {
      int sum = matrix_get(m1, i, j) + matrix_get(m2, i, j);
      matrix_set(result, i, j, sum);
    }
  }

  return result;
}

inline matrix *matrix_multiply(matrix *m1, matrix *m2) {
  assert(m1->col == m2->row);

  matrix *result = matrix_create(m1->row, m2->col);

  for (unsigned i = 0; i < m1->row; i++) {
    for (unsigned j = 0; j < m2->col; j++) {
      float sum = 0;
      for (unsigned k = 0; k < m1->col; k++) {
        sum += matrix_get(m1, i, k) * matrix_get(m2, k, j);
      }
      matrix_set(result, i, j, sum);
    }
  }

  return result;
}

inline matrix *matrix_sqrt(matrix *m) {
  assert(m->row == m->col);

  matrix *result = matrix_create(m->row, m->col);

  for (unsigned i = 0; i < m->row; i++) {
    for (unsigned j = 0; j < m->col; j++) {
      float value = matrix_get(m, i, j);
      float root = sqrt(value);
      matrix_set(result, i, j, root);
    }
  }

  return result;
}

inline void matrix_print(matrix *m) {
  for (unsigned i = 0; i < m->row; i++) {
    for (unsigned j = 0; j < m->col; j++) {
      float value = matrix_get(m, i, j);
      printf("%08.02f ", value);
    }
    printf("\n");
  }
}
