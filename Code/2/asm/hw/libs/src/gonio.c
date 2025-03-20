#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14159265358979323846

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

static double (*sin_func)(double) = NULL;
static double (*cos_func)(double) = NULL;
static double (*tan_func)(double) = NULL;

double deg_to_rad(long degrees) { return degrees * M_PI / 180.0; }

int get_sin(long degrees) {
  double radians = deg_to_rad(degrees);
  double sin_value = sin_func(radians);
  printf("sin(%ld°) = %f\n", degrees, sin_value);
  return EXIT_SUCCESS;
}

int get_cos(long degrees) {
  double radians = deg_to_rad(degrees);
  double cos_value = cos_func(radians);
  printf("cos(%ld°) = %f\n", degrees, cos_value);
  return EXIT_SUCCESS;
}

int get_tan(long degrees) {
  double radians = deg_to_rad(degrees);
  double tan_value = tan_func(radians);
  printf("tan(%ld°) = %f\n", degrees, tan_value);
  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  OPERATION operation = INVALID;
  long degrees = 0;
  void *handle = NULL;
  int ret = EXIT_FAILURE;

  if (argc != 3) {
    usage();
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "sin") == 0) {
    operation = SIN;
  } else if (strcmp(argv[1], "cos") == 0) {
    operation = COS;
  } else if (strcmp(argv[1], "tan") == 0) {
    operation = TAN;
  } else {
    operation = INVALID;
  }

  degrees = strtol(argv[2], NULL, 10);

  handle = dlopen("libm.so.6", RTLD_LAZY); // My system's libm.so
  if (!handle) {
    fprintf(stderr, "Error loading math library: %s\n", dlerror());
    return EXIT_FAILURE;
  }

  dlerror(); // Clear any existing error

  sin_func = (double (*)(double))dlsym(handle, "sin");
  cos_func = (double (*)(double))dlsym(handle, "cos");
  tan_func = (double (*)(double))dlsym(handle, "tan");

  char *error = dlerror();
  if (error) {
    fprintf(stderr, "Error resolving symbols: %s\n", error);
    dlclose(handle);
    return EXIT_FAILURE;
  }

  switch (operation) {
  case SIN:
    ret = get_sin(degrees);
    break;
  case COS:
    ret = get_cos(degrees);
    break;
  case TAN:
    ret = get_tan(degrees);
    break;
  case INVALID:
    printf("Invalid syntax\n");
    usage();
    ret = EXIT_FAILURE;
    break;
  }

  dlclose(handle);
  return ret;
}
