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

int **report_occurences(char *text, char **patterns, int n) {
  int **ret = malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++) {
    char *pattern = patterns[i];
    int patternLength = 0;
    int count = 0;
    int line = 1;

    while (pattern[patternLength] != '\0')
      patternLength++;

    for (int j = 0; text[j] != '\0'; j++) {
      if (text[j] == '\n')
        line++;
      int match = 1;
      for (int k = 0; k < patternLength; k++) {
        if (text[j + k] == '\0' || text[j + k] != pattern[k]) {
          match = 0;
          break;
        }
      }
      if (match)
        count++;
    }
    ret[i] = malloc((count + 1) * sizeof(int));
    ret[i][0] = count;
    line = 1;
    int index = 1;
    for (int j = 0; text[j] != '\0'; j++) {
      if (text[j] == '\n')
        line++;
      int match = 1;
      for (int k = 0; k < patternLength; k++) {
        if (text[j + k] == '\0' || text[j + k] != pattern[k]) {
          match = 0;
          break;
        }
      }
      if (match)
        ret[i][index++] = line;
    }
  }
  return ret;
}

int main(void) {
  char *text = "TestTest\nTest1\nTest\nTest2\nTest3\n";
  char *patterns[] = {"Test", "Test2"};
  int pattern_count = sizeof(patterns) / sizeof(patterns[0]);

  printf("Text:\n");
  printf("```\n");
  printf("%s", text);
  printf("```\n");

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
    free(result[i]);
  }

  free(result);
  return 0;
}

// Konya

// Expected output:
/*
Text:
```
TestTest
Test1
Test
Test2
Test3
```

Pattern: `Test`
Count: 6
Lines: [1, 1, 2, 3, 4, 5]

Pattern: `Test2`
Count: 1
Lines: [4]
*/
