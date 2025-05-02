#include <stdio.h>
#include <stdlib.h>

void print_array(int a[], int count) {
  printf("[");
  for (int i = 0; i < count; i++) {
    printf("%i", a[i]);
    if (i < count - 1)
      printf(", ");
  }
  printf("]\n");
}

int str_cmp(char *s1, char *s2, int len) {
  for (int i = 0; i < len; i++) {
    if (s1[i] != s2[i])
      return 0;
  }
  return 1;
}

int str_len(char *s) {
  int len = 0;
  while (*s) {
    len++;
    s++;
  }
  return len;
}

int count_lines(char *text) {
  int count = 1;
  while (*text) {
    if (*text == '\n')
      count++;
    text++;
  }
  return count;
}

int **report_occurences(char *text, char **patterns, int n) {
  int **result = malloc(n * sizeof(int *));
  char *line = text;
  int line_number = 1;
  int line_count = count_lines(text);

  for (int i = 0; i < n; i++) {
    result[i] = malloc((line_count + 1) * sizeof(int));
    result[i][0] = 0; // Count of occurrences
  }

  while (*line) {
    for (int i = 0; i < n; i++) {
      char *pattern = patterns[i];
      int pattern_len = str_len(pattern);
      if (str_cmp(line, pattern, pattern_len)) {
        result[i][++result[i][0]] = line_number;
      }
    }
    if (*line == '\n') {
      line_number++;
    }
    line++;
  }

  return result;
}

void print_text(char text[], int len) {
  int line_number = 1;

  printf("Line | Text\n");
  printf("-----|----------------\n");

  for (int i = 0; i < len; i++) {
    if (i == 0 || text[i - 1] == '\n') {
      printf("%4d | ", line_number);
      line_number++;
    }

    if (text[i] != '\n') {
      putchar(text[i]);
    } else {
      printf("\\n");
      printf("\n");
    }
  }
}

int main(void) {
  char text[] = "TestTest\nTest1\nTest\nTest2\nTest3\n";
  int text_size = sizeof(text) / sizeof(text[0]);

  char *patterns[] = {"Test", "Test2", "Test4"};
  int pattern_count = sizeof(patterns) / sizeof(patterns[0]);

  print_text(text, text_size);
  printf("\n");

  int **result = report_occurences(text, patterns, pattern_count);

  for (int i = 0; i < pattern_count; i++) {
    char *pattern = patterns[i];
    int *lines_array = result[i] + 1;
    int lines_count = result[i][0];

    printf("\n");
    printf("Pattern: `%s`\n", pattern);
    printf("Count: %d\n", lines_count);
    printf("Lines: ");
    print_array(lines_array, lines_count);
  }

  free(result);
  return 0;
}

// Konya

// Expected output:
/*
Line | Text
-----|----------------
   1 | TestTest\n
   2 | Test1\n
   3 | Test\n
   4 | Test2\n
   5 | Test3\n
   6 |

Pattern: `Test`
Count: 6
Lines: [1, 1, 2, 3, 4, 5]

Pattern: `Test2`
Count: 1
Lines: [4]

Pattern: `Test4`
Count: 0
Lines: []
*/
