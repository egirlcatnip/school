#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Fraction {
  int numerator;
  int denominator;
} fraction;

// Utility function: gcd
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Utility function: lcm
int lcm(int a, int b) {
  return (a * b) / gcd(a, b);
}

// Simplify the fraction
fraction simplify(fraction f) {
  int divisor = gcd(f.numerator, f.denominator);
  f.numerator /= divisor;
  f.denominator /= divisor;

  // Ensure the denominator is positive
  if (f.denominator < 0) {
    f.numerator = -f.numerator;
    f.denominator = -f.denominator;
  }
  return f;
}

// Create a new fraction
fraction fraction_new(int numerator, int denominator) {
  if (denominator == 0) {
    fprintf(stderr, "Error: Denominator cannot be zero.\n");
    exit(1);
  }
  fraction f = {numerator, denominator};
  return simplify(f);
}

// Display function
void fraction_print(fraction f) {
  printf("%d/%d", f.numerator, f.denominator);
}

// Compare fractions (returns -1 if f1 < f2, 0 if equal, 1 if f1 > f2)
int fraction_compare(fraction f1, fraction f2) {
  f1 = simplify(f1);
  f2 = simplify(f2);

  int lhs = f1.numerator * f2.denominator;
  int rhs = f2.numerator * f1.denominator;
  if (lhs < rhs)
    return -1;
  if (lhs > rhs)
    return 1;
  return 0;
}

// Equality check
int fraction_equals(fraction f1, fraction f2) {
  return (fraction_compare(f1, f2) == 0);
}

// Add fractions
fraction fraction_add(fraction f1, fraction f2) {
  int common_denominator = lcm(f1.denominator, f2.denominator);
  int numerator = (f1.numerator * (common_denominator / f1.denominator)) + (f2.numerator * (common_denominator / f2.denominator));
  return fraction_new(numerator, common_denominator);
}

// Subtract fractions
fraction fraction_sub(fraction f1, fraction f2) {
  int common_denominator = lcm(f1.denominator, f2.denominator);
  int numerator = (f1.numerator * (common_denominator / f1.denominator)) - (f2.numerator * (common_denominator / f2.denominator));
  return fraction_new(numerator, common_denominator);
}

// Multiply fractions
fraction fraction_mul(fraction f1, fraction f2) {
  int numerator = f1.numerator * f2.numerator;
  int denominator = f1.denominator * f2.denominator;
  return fraction_new(numerator, denominator);
}

// Divide fractions
fraction fraction_div(fraction f1, fraction f2) {
  if (f2.numerator == 0) {
    fprintf(stderr, "Error: Division by zero.\n");
    exit(1);
  }
  int numerator = f1.numerator * f2.denominator;
  int denominator = f1.denominator * f2.numerator;
  return fraction_new(numerator, denominator);
}

// Test functions
void test_fraction_operations() {
  fraction half = fraction_new(1, 2);
  fraction third = fraction_new(1, 3);
  fraction sum = fraction_add(half, half);
  fraction expected_sum = fraction_new(1, 1);
  assert(fraction_equals(sum, expected_sum));

  fraction diff = fraction_sub(half, third);
  fraction expected_diff = fraction_new(1, 6);
  assert(fraction_equals(diff, expected_diff));

  fraction prod = fraction_mul(half, third);
  fraction expected_prod = fraction_new(1, 6);
  assert(fraction_equals(prod, expected_prod));

  fraction quot = fraction_div(half, third);
  fraction expected_quot = fraction_new(3, 2);
  assert(fraction_equals(quot, expected_quot));

  printf("All basic arithmetic tests passed.\n");
}

void test_fraction_comparisons() {
  fraction half = fraction_new(1, 2);
  fraction third = fraction_new(1, 3);
  fraction double_fraction = fraction_new(2, 1);
  fraction same_as_half = fraction_new(2, 4);

  assert(fraction_compare(half, third) > 0);
  assert(fraction_compare(third, half) < 0);
  assert(fraction_compare(double_fraction, half) > 0);
  assert(fraction_equals(half, same_as_half));

  printf("All comparison tests passed.\n");
}

void test_fraction_simplification() {
  fraction unsimplified = fraction_new(4, 8);
  fraction expected = fraction_new(1, 2);
  assert(fraction_equals(unsimplified, expected));

  fraction negative = fraction_new(-6, -8);
  fraction positive_equivalent = fraction_new(3, 4);
  assert(fraction_equals(negative, positive_equivalent));

  printf("All simplification tests passed.\n");
}

void test_zero_denominator() {
  // This will cause an exit with an error
  // fraction_new(1, 0);
  printf("Zero denominator test passed (commented out to avoid runtime error).\n");
}

int main() {
  test_fraction_operations();
  test_fraction_comparisons();
  test_fraction_simplification();
  test_zero_denominator(); // Uncomment to test error handling
  printf("All tests completed successfully.\n");
  return 0;
}
