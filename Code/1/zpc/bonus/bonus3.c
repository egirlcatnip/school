#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int fast_sqrt(int n) {
  int x = n;
  int y = (x + 1) / 2;

  while (y < x) {
    x = y;
    y = (x + n / x) / 2;
  }

  return x;
}

// Helper functions
int get_matrix_by_index(int r[], int m, int index_x, int index_y) {
  // Check if indices are within bounds
  assert(index_x >= 0 && index_x < m && index_y >= 0 && index_y < m);

  // Check for valid values in the matrix (0 or 1)
  int value = r[index_x * m + index_y];
  assert(value == 0 || value == 1);

  return value;
}

void set_matrix_by_index(int r[], int m, int index_x, int index_y, int value) {
  // Check if indices are within bounds
  assert(index_x >= 0 && index_x < m && index_y >= 0 && index_y < m);

  // Check for valid values (0 or 1)
  assert(value == 0 || value == 1);

  r[index_x * m + index_y] = value;
}

void print_matrix(int r[], int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value = get_matrix_by_index(r, m, i, j);
      printf("%d  ", value);
    }
    printf("\n");
  }
}

// Checks
int symetric(int r[], int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int value_i = get_matrix_by_index(r, m, i, j);
      int value_j = get_matrix_by_index(r, m, j, i);

      if (value_i != value_j) {
        return false;
      }
    }
  }
  return true;
}

int reflexive(int r[], int m) {
  for (int i = 0; i < m; i++) {
    int value = get_matrix_by_index(r, m, i, i);

    if (value == 0) {
      return false;
    }
  }
  return true;
}

int transitive(int r[], int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        int value_i = get_matrix_by_index(r, m, i, j);
        int value_j = get_matrix_by_index(r, m, j, k);
        int value_k = get_matrix_by_index(r, m, i, k);

        if (value_i && value_j && !value_k) {
          return false;
        }
      }
    }
  }
  return true;
}

void print_equivalence(int r[], int m) {
  int is_reflexive = reflexive(r, m);
  int is_symetric = symetric(r, m);
  int is_transitive = transitive(r, m);

  if (is_reflexive) {
    printf(GREEN "The matrix is reflexive.\n" RESET);
  } else {
    printf(RED "The matrix is not reflexive.\n" RESET);
  }
  if (is_symetric) {
    printf(GREEN "The matrix is symetric.\n" RESET);
  } else {
    printf(RED "The matrix is not symetric.\n" RESET);
  }
  if (is_transitive) {
    printf(GREEN "The matrix is transitive.\n" RESET);
  } else {
    printf(RED "The matrix is not transitive.\n" RESET);
  }
}

// Exercise functions
int equivalence(int r[], int m) {
  int is_reflexive = reflexive(r, m);
  int is_symetric = symetric(r, m);
  int is_transitive = transitive(r, m);

  return (is_symetric && is_transitive && is_reflexive);
}

void transitive_closure(int r[], int m) {
  for (int k = 0; k < m; k++) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (get_matrix_by_index(r, m, i, k) &&
            get_matrix_by_index(r, m, k, j)) {
          set_matrix_by_index(r, m, i, j, 1);
        }
      }
    }
  }

  if (!transitive(r, m)) {
    printf(RED "Transitive closure failed.\n" RESET);
    return;
  }

  printf("Updated with transitive closure:\n");
  print_matrix(r, m);
}

int main(void) {
  int matrix[] = {
      1, 1, 0, 0, //
      0, 1, 1, 0, //
      0, 0, 1, 1, //
      0, 0, 0, 1, //
  };

  int total_elements = sizeof(matrix) / sizeof(matrix[0]);
  int m = fast_sqrt(total_elements);

  if (m * m != total_elements) {
    printf(RED "Invalid matrix size.\n" RESET);
    return -1;
  }

  printf("Matrix:\n");
  print_matrix(matrix, m);
  printf("\n");

  int equivalent = equivalence(matrix, m);

  if (equivalent) {
    print_equivalence(matrix, m);
    printf(GREEN "The matrix is equivalent.\n" RESET);
  } else {
    printf(RED "The matrix is not equivalent.\n" RESET);
    print_equivalence(matrix, m);
  }

  printf("\n");

  int is_transitive = transitive(matrix, m);

  if (is_transitive) {
    printf(GREEN "The matrix is already transitive.\n" RESET);
  } else {
    transitive_closure(matrix, m);
  };

  printf("\n");

  if (equivalent) {
    print_equivalence(matrix, m);
    printf(GREEN "The matrix is equivalent.\n" RESET);
  } else {
    printf(RED "The matrix is not equivalent.\n" RESET);
    print_equivalence(matrix, m);
  }

  return 0;
}

// Konya

/*
Matrix:
1  1  0  0
0  1  1  0
0  0  1  1
0  0  0  1

The matrix is not equivalent.
The matrix is reflexive.
The matrix is not symetric.
The matrix is not transitive.

Updated with transitive closure:
1  1  1  1
0  1  1  1
0  0  1  1
0  0  0  1

The matrix is not equivalent.
The matrix is reflexive.
The matrix is not symetric.
The matrix is transitive.
*/
