#include <stdio.h>

void convertFahrenheitToCelsius(float fahrenheit) {
  if (fahrenheit >= -459.16) {
    float celsius = ((5 * (fahrenheit - 32)) / 9);
    printf("%0.2f Fahrenheit is %0.2f Celsius.\n", fahrenheit, celsius);
  }
  else {
    printf("The temperature in Fahrenheit must be above -459.16\n");
  }
}

void printNumbersUpToTen() {
  for (int n = 0; n <= 10; n++) {
    printf("%i\n", n);
  }
}
double calculatePiUsingLeibnizSeries(int precision) {
  double value = 0.0;
  for (int n = 0; n <= precision; n++) {

    value += ((n % 2 == 0 ? 1.0 : -1.0) / (2 * n + 1));
  }
  return value * 4.0;
}

void displayPiWithPrecision() {
  int precision = 10000000;
  float pi = calculatePiUsingLeibnizSeries(precision);
  printf("Pi with precision of %i:\n%.22f\n", precision, pi);
}

void printIncreasingNumberTriangle(int rows) {
  int maxValue = 1;
  for (int row = 1; row <= rows; row++, maxValue++) {
    for (int column = 1; column <= maxValue; column++) {
      printf("%i ", column);
    }
    printf("\n");
  }
}

void printSequentialNumberTriangle(int rows) {
  int currentNum = 1;
  for (int row = 1; row <= rows; row++) {
    for (int col = 1; col <= row; col++) {
      printf("%i ", currentNum);
      currentNum++;
    }
    printf("\n");
  }
}

void printPyramidPattern(int rows) {
  for (int row = 1; row <= rows; row++) {
    for (int space = 1; (space <= rows - row); space++) {
      printf(" ");
    }
    for (int col = 1; col <= row; col++) {
      printf("* ");
    }
    printf("\n");
  }
}

void euclid(int a, int b) {
  while (b) {
    int x = a;
    a = b;
    b = x % b;
  }
  printf("Result: %i\n", a);
};

int grade() {
  int score;

  printf("Enter your score (0-100): ");

  // Read the input
  if (scanf("%d", &score) != 1) {
    printf("Invalid input. Please enter an integer.\n");
    return 1;
  }

  // Check if the score is within the valid range
  if (score < 0 || score > 100) {
    printf("Invalid score. Enter a number between 0 and 100.\n");
    return 1;
  }

  // Determine the grade
  if (score >= 90) {
    printf("Your grade is: A\n");
  }
  else if (score >= 80) {
    printf("Your grade is: B\n");
  }
  else if (score >= 70) {
    printf("Your grade is: C\n");
  }
  else if (score >= 60) {
    printf("Your grade is: D\n");
  }
  else {
    printf("Your grade is: F\n");
  }
  return 1;
};

void letter_count(int a, int b) {
  int result = b;
  for (int i = 0; (i < a); i++) {
    printf("%i\n", result);
    result += b;
  }
};

void power(int a, int b) {
  printf("%i^%i\n", a, b);
  int result = 1;

  if (b == 0) {
    printf("result is: 1\n");
  }
  else {
    for (int i = 0; i < b; i++) {
      result *= a;
    };
    printf("result is: %i\n", result);
  }
};

void fib(int n) {

  int m = 0;
  int v = 1;
  int next;

  for (int i = 2; i <= n; i++) {
    next = m + v;
    m = v;
    v = next;
  }
  printf("result is: %i\n", v);
};

// Returns 0 if not a palindrome, else returns n
int palindrome(int n) {
  int original = n;
  // printf("Input: %i \n", n);

  while (n / 10 != 0) {
    int divisor = 1;
    int first_digit = n;

    // Find the first digit and the divisor
    while (first_digit / 10 != 0) {
      first_digit /= 10;
      divisor *= 10;
    }

    // Find the last digit
    int last_digit = n % 10;

    // Check if the first and last digits are the same
    if (first_digit != last_digit) {
      return 0;
    }

    // Remove the first and last digits
    n = n - (first_digit * divisor);
    n = n / 10;
  }

  return original;
}

// More efficient palindrome check
// Returns 0 if not a palindrome, else returns n
int palindrome2(int n) {

  int original = n;
  int reversed = 0;

  while (n != 0) {
    int last_digit = n % 10;
    reversed = reversed * 10 + last_digit;
    n /= 10;
  }

  // Compare reversed to original
  if (original == reversed) {
    return original;
  }
  else {
    return 0;
  }
};

void palindrome_range(int a, int b) {

  for (; a <= b; a++) {

    // printf("Input: %i\n", a);

    if (palindrome2(a)) {
      printf("Palindrome: %i\n", a);
    }
  };
};

int main() {
  // convertFahrenheitToCelsius(120);

  // displayPiWithPrecision();

  // printIncreasingNumberTriangle(10);

  // printPyramidPattern(4);

  // euclid(21, 24);

  // grade();

  // arrays

  // nasobky(2, 8);

  // power(2, 8);

  // fib(10);

  // palindrome(101);

  palindrome_range(1, 100);
  return 0;
}
