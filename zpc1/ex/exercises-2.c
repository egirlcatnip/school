#include <stdio.h>

int best_index = 0;
int best_len = 0;

int str_len(char string[]) {
  int len = 0;
  while (string[len] != '\0') {
    len++;
  }
  return len;
}

void search(char string1[], char string2[], int string1_len, int string2_len) {
  int connection_from_end = 0;
  for (int i = string1_len - 1; i >= 0; i--) {
    int j = 0;

    for (; string1[i + j] && string2[j]; j++) {
      if (string1[i + j] != string2[j]) {
        break;
      };
    };

    if (!string1[i + j] || !string2[j]) {
      connection_from_end = j;
    }
  }
  printf("Connects from end at index: -%i \n", connection_from_end);
}

int main() {
  char string1[] = "ahoj svete ahshoda na konci";
  char string2[] = "nci shoda na zacatku";

  int string1_len = str_len(string1);
  int string2_len = str_len(string2);

  // Checks
  if (string1_len <= 0) {
    printf("String must be of size larger than 0\n");
    return 1;
  };
  if (string2_len <= 0) {
    printf("String must be of size larger than 0\n");
    return 1;
  };

  printf("String: \"%s\"\n", string1);
  printf("Looking for: \"%s\"\n", string2);

  search(string1, string2, string1_len, string2_len);

  return 0;
}

// Konya
/*
String: "ahoj svete ahshoda na konci"
Looking for: "nci shoda na zacatku"
Connects from end at index: -3
*/