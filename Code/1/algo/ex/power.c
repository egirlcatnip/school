#include <stdio.h>

int power_iter(int n, int exponent) {
  if (exponent == 0) {
    return 1;
  }
  if (exponent == 1) {
    return n;
  }

  return n * power_iter(n, exponent - 1);
}

int power_tail_iter(int n, int exponent, int accumulated) {
  if (exponent == 0) {
    return accumulated;
  }

  return power_tail_iter(n, exponent - 1, n * accumulated);
}

void power(int n, int exp) {
  // int result = power_iter(n, exp);

  int result = power_tail_iter(n, exp, 1);

  printf("%i^%i is: %i\n", n, exp, result);
}

int main() {

  power(2, 8); // 256

  return 0;
}
