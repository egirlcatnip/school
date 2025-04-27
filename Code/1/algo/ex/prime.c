#include <stdio.h>

int is_prime_iter(int n, int divisor) {
  if (n <= 1) {
    return 0;
  }

  // Optimazitazion O(n) -> O(sqrt(n))
  if ((divisor * divisor) > n) {
    return 1;
  }

  if (divisor == n) {
    return 1;
  }

  if (n % divisor == 0) {
    return 0;
  }

  return is_prime_iter(n, divisor + 1);
}

int is_prime(int n) { return is_prime_iter(n, 2); }

void prime(int n) {

  int result = is_prime(n);

  if (result) {
    printf("Number %i is prime\n", n);
  } else {
    printf("Number %i is prime\n", n);
  }
}

void prime_count(int input) {

  int prime_count = 1;
  for (int n = 0; prime_count <= input; n++) {
    int current = is_prime(n);

    if (current) {
      printf("Prime %i:\t %i\n", prime_count, n);
      prime_count++;
    }
  }
}
#include <stdio.h>

void prime_divisor(int n) {
  if (n <= 0) {
    printf("Only for positive numbers\n");
    return;
  }

  printf("Number %i has these prime factors:\n", n);

  for (int i = 2; i <= n; i++) {
    if (n % i == 0 && is_prime(i)) {
      while (n % i == 0) {
        printf("%i\n", i);
        n /= i;
      }
    }
  }
}

int main() {
  // prime(13);

  // prime_count(32);

  prime_divisor(24);

  return 0;
}
