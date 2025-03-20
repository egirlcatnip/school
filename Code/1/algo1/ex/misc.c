#include <stdint.h>
#include <stdio.h>
#include <string.h>

void letter_count(char string[]) {
  printf("Your string is:\n\"%s\"\n", string);

  int alphabet[26] = {0}; // Array of 26 filled with zeroes
  int str_len = strlen(string);

  for (int i = 0; i < str_len; i++) {
    char character = string[i];
    if (character >= 'A' && character <= 'Z') {
      character = character + 32; // A -> a
    }

    if (character >= 'a' && character <= 'z') {
      alphabet[character - 'a']++; // Count letter occurences
    }
  }

  for (char value = 'a'; value <= 'z'; value++) {
    int count = alphabet[value - 'a'];
    if (count != 0) {
      printf("The letter '%c' is found %d times\n", value, count);
    }
  }
}

void multiplication_table(int n) {
  printf("Multiplication Table up to %d:\n", n);

  for (int i = 1; i <= n; i++) {

    for (int j = 1; j <= n; j++) {
      printf("%i\t", i * j);
    }
    printf("\n");
  }
}

void even_odd(int n) {
  if (n % 2 == 0) {
    printf("The number %i is even\n", n);
  } else
    printf("The number %i is odd\n", n);
}

void multipilication1(int a, int b) {
  int result = 0;
  for (int i = 1; i <= b; i++)
    result += a;

  printf("%d * %d = %d\n", a, b, result);
}

void addition(int a, int b) {
  printf("Adding together %i + %i\n", a, b);
  int final_number = 0;
  int carry = 0;
  int place_multiplier = 1;

  printf("Addition in steps:\n");
  int n = 0;

  while (a != 0 || b != 0 || carry != 0) {
    n = n + 1;
    int a_last = a % 10;
    int b_last = b % 10;

    int added = a_last + b_last + carry;
    int final_digit = added % 10;
    carry = added / 10;

    final_number += final_digit * place_multiplier;

    printf("+%*i, carry: %i\n", 16, final_digit * place_multiplier, carry);

    // Update for next place value
    place_multiplier *= 10;
    a /= 10;
    b /= 10;
  }

  printf("\nFinal number: %d\n", final_number);
}

int main() {

  // letter_count("Matematika");

  // multipilication1(2, 4);

  addition(9, 1);

  return 0;
}
