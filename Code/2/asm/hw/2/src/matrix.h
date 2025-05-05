#ifndef MATRIX_H
#define MATRIX_H
#include <assert.h>

typedef struct {
  float *data;
  unsigned row;
  unsigned col;
} matrix;

matrix *matrix_create(unsigned row, unsigned col);

void matrix_free(matrix *m);

static inline float matrix_get(matrix *m, unsigned row, unsigned col) {
  assert(row < m->row && col < m->col);
  return m->data[row * m->col + col];
}

static inline void matrix_set(matrix *m, unsigned row, unsigned col,
                              float val) {
  assert(row < m->row && col < m->col);
  m->data[row * m->col + col] = val;
}

matrix *matrix_set_fromarray(matrix *m, float *array, unsigned size);

matrix *matrix_add(matrix *m1, matrix *m2);

matrix *matrix_multiply(matrix *m1, matrix *m2);

matrix *matrix_sqrt(matrix *m);

void matrix_print(matrix *m);

#endif // MATRIX_H
