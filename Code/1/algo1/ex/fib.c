#include <stdio.h>

int fib_inefficient(int n) {
  if (n <= 1) {
    return n;
  } else {
    return fib_inefficient(n - 2) + fib_inefficient(n - 1);
  }
}

int fib_tail_rec_iter(int n, int previous, int current) {
  printf("n, previous, current: %i, %i, %i \n", n, previous, current); // Debug
  if (n == 0)
    return previous;
  if (n == 1)
    return current;

  return fib_tail_rec_iter(n - 1, current, previous + current);
}

int fib_tail_rec(int n) { return fib_tail_rec_iter(n, 0, 1); }

int main() {
  int position = 5;

  // int number = fib_inefficient(position);

  int result = fib_tail_rec(position);

  printf("Fibonacci on the position of %i is %i", position, result);

  return 0;
}
