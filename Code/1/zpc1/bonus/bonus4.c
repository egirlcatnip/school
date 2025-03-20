#include <stdio.h>

void split_two_numbers(char src[], char num1[], char num2[]) {
  int i = 0, j = 0;
  while (src[i] != ' ' && src[i] != '\0') {
    num1[i] = src[i];
    i++;
  }
  num1[i] = '\0';
  i++;
  while (src[i] != '\0') {
    num2[j] = src[i];
    i++;
    j++;
  }
  num2[j] = '\0';
}

int get_length(char num[]) {
  int len = 0;
  while (num[len] != '\0')
    len++;
  return len;
}

int char_to_digit(char c) { return c - '0'; }

char digit_to_char(int i) { return i + '0'; }

int add_numbers(char num1[], char num2[], char sum[], int max_len) {
  int len1 = get_length(num1);
  int len2 = get_length(num2);

  int carry = 0;
  int sum_len = 0;

  for (int p1 = len1 - 1, p2 = len2 - 1; p1 >= 0 || p2 >= 0 || carry;
       p1--, p2--) {
    int digit1 = 0;
    if (p1 >= 0) {
      digit1 = char_to_digit(num1[p1]);
    }

    int digit2 = 0;
    if (p2 >= 0) {
      digit2 = char_to_digit(num2[p2]);
    }

    int digit_sum = digit1 + digit2 + carry;
    if (sum_len >= max_len) {
      return 0;
    }

    int digit = digit_sum % 10;
    carry = digit_sum / 10;

    sum[sum_len] = digit_to_char(digit);
    sum_len++;
  }

  sum[sum_len] = '\0';
  return sum_len;
}

int compute_sum(char src[], char result[], int n) {
  int array_len = n;
  char num1[array_len];
  char num2[array_len];
  char sum[array_len];

  split_two_numbers(src, num1, num2);

  int sum_len = add_numbers(num1, num2, sum, n - 1);

  if (sum_len == 0 || sum_len >= n) {
    return 0;
  }

  for (int i = 0; i < sum_len; i++) {
    result[i] = sum[sum_len - i - 1];
  }

  result[sum_len] = '\0';
  return 1;
}

int main(void) {
  char src[] = "1234 8766";
  // char src[] = "12340000000000000000000000000 87660000000000000000000000000";
  // // example of long input
  int result_len = 600; // Does not overflow
  // int result_len = 5; // Overflows

  char result[result_len];

  int v = compute_sum(src, result, result_len);

  printf("Input : %s\n", src);
  if (v) {
    printf("Sum   : %s\n", result);
    return 0;
  } else {
    printf("Sum: N/A, overflow\n");
    return 1;
  }
}

// Konya

/*
Input : 1234 8766
Sum   : 10000
*/
