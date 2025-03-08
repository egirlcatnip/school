#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  INVALID,
  SIN,
  COS,
  TAN,
} OPERATION;

void usage(void) {
  printf("Usage:\n");
  printf("\tgonio sin <degrees>\n");
  printf("\tgonio cos <degrees>\n");
  printf("\tgonio tan <degrees>\n");
}

int get_sin(long degrees) {
  double radians = degrees * M_PI / 180.0;
  double sin_value = sin(radians);
  printf("sin(%ld°) = %f\n", degrees, sin_value);
  return EXIT_SUCCESS;
}

int get_cos(long degrees) {
  double radians = degrees * M_PI / 180.0;
  double cos_value = cos(radians);
  printf("cos(%ld°) = %f\n", degrees, cos_value);
  return EXIT_SUCCESS;
}

int get_tan(long degrees) {
  double radians = degrees * M_PI / 180.0;
  double tan_value = tan(radians);
  printf("tan(%ld°) = %f\n", degrees, tan_value);
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  OPERATION operation = INVALID;
  long degrees = 0;

  if (argc != 3) {  // Fix argument count check
    usage();
    return EXIT_FAILURE;
  }

  if (!strcmp(argv[1], "sin")) {
    operation = SIN;
  } else if (!strcmp(argv[1], "cos")) {
    operation = COS;
  } else if (!strcmp(argv[1], "tan")) {
    operation = TAN;
  } else {
    operation = INVALID;
  }

  degrees = strtol(argv[2], NULL, 10);  // Fix strtol usage

  switch (operation) {
    case SIN: {
      return get_sin(degrees);
    }

    case COS: {
      return get_cos(degrees);
    }

    case TAN: {
      return get_tan(degrees);
    }

    case INVALID:
      printf("Invalid syntax\n");
      usage();
      return EXIT_FAILURE;
  }
}
