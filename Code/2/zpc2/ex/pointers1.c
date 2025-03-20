#include <stddef.h>
#include <stdio.h>

void print_array(int *a, int a_len) {
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

int main(void) {
  // Variable
  int x = 10;
  int *ptr_x = &x;

  // Pointer dereference
  int y = x;
  int *ptr_y = &y;

  printf("Pointers:\n");
  printf("Pointer of x(%d) is %p\n", x, ptr_x); // Different pointer addresses
  printf("Pointer of y(%d) is %p\n", y, ptr_y); // same values
  printf("Deref of x(%d)   is %d\n", x, *ptr_x);

  printf("\n");

  // Array syntax
  int array1[] = {1, 2, 3};

  // Pointer syntax
  int *array2 = array1;

  // Reference syntax
  int *array3 = &(*(array2));

  int size = sizeof(array1) / sizeof(array1[0]);

  // Same values
  printf("Arrays:\n");
  printf("array1: ");
  print_array(array1, size); // [1, 2, 3]
  printf("array2: ");
  print_array(array2, size); // [1, 2, 3]
  printf("array3: ");
  print_array(array3, size); // [1, 2, 3]

  printf("\n");

  // Different sizes
  printf("Sizes:\n");
  printf("sizeof(int):    %2.zi\n", sizeof(x));      // 4
  printf("sizeof(ptr):    %2.zi\n", sizeof(&x));     // 8
  printf("sizeof(array1): %2.zi\n", sizeof(array1)); // 12 (int * 3)
  printf("sizeof(array2): %2.zi\n", sizeof(array2)); // 8  (int *)
  printf("sizeof(array3): %2.zi\n", sizeof(array3)); // 8  (int *)

  return 0;
}

// Konya
