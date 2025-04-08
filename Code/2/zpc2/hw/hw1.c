#include <stdio.h>
#include <stdlib.h>

void print_array(int a[], int a_len) {
  printf("[");
  for (int i = 0; i < a_len; i++) {
    printf("%i", a[i]);
    if (i < a_len - 1) {
      printf(", ");
    }
  }
  printf("]");
  printf("\n");
}

int **report_occurences(char *text, char **patterns, int n) {
  int **ret = (int **)malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++) {
    char *pattern = patterns[i];
    int pattern_len = 0, count = 0, line = 1;

    while (pattern[pattern_len] != '\0')
      pattern_len++;

    for (int j = 0; text[j] != '\0'; j++) {
      if (text[j] == '\n')
        line++;

      int match = 1;
      for (int k = 0; k < pattern_len; k++) {
        if (text[j + k] == '\0' || text[j + k] != pattern[k]) {
          match = 0;
          break;
        }
      }

      if (match)
        count++;
    }

    ret[i] = (int *)malloc((count + 1) * sizeof(int));
    ret[i][0] = count;
    count = 0;
    line = 0;

    for (int j = 0; text[j] != '\0'; j++) {
      if (text[j] == '\n')
        line++;

      int match = 1;
      for (int k = 0; k < pattern_len; k++) {
        if (text[j + k] == '\0' || text[j + k] != pattern[k]) {
          match = 0;
          break;
        }
      }

      if (match)
        ret[i][++count] = line;
    }
  }
  return ret;
}

int main(void) {
  char *text = "Test\nTest2\nTest\nTest3\nTest2\n";
  char *patterns[] = {"Test", "Test2"};
  int len = sizeof(patterns) / sizeof(patterns[0]);

  printf("Text:\n");
  printf("```\n");
  printf("%s", text);
  printf("```\n");
  printf("\n");
  printf("\n");

  int **result = report_occurences(text, patterns, len);

  for (int i = 0; i < len; i++) {
    printf("Pattern: `%s`\n", patterns[i]);
    printf("Count: %d\n", result[i][0]);

    printf("Lines: "); // 0-index based
    print_array(result[i] + 1, result[i][0]);
    printf("\n");
    free(result[i]);
  }
  free(result);
  return 0;
}
