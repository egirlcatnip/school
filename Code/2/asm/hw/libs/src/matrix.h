#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  float *data;
  unsigned row;
  unsigned col;
} matrix;

matrix *matrix_create(unsigned row, unsigned col);

void matrix_free(matrix *m);

float matrix_get(matrix *m, unsigned row, unsigned col);

void matrix_set(matrix *m, unsigned row, unsigned col, float val);

matrix *matrix_set_fromarray(matrix *m, float *array, unsigned size);

matrix *matrix_add(matrix *m1, matrix *m2);

matrix *matrix_multiply(matrix *m1, matrix *m2);

matrix *matrix_sqrt(matrix *m);

void matrix_print(matrix *m);

#endif // MATRIX_H
