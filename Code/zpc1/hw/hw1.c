#include <stdbool.h>
#include <stdio.h>

void print_by_index(char str[], int index_start, int index_end) {
  printf("\"");
  for (int i = index_start; i < index_end; i++) {
    printf("%c", str[i]);
  }
  printf("\"");
  printf("\n");
}

int str_len(char str[]) {
  int str_len = 0;
  while (str[str_len] != '\0') {
    str_len++;
  }
  return str_len;
}

int word_end_index(char str[], int str_len, int start_index) {
  int i = start_index;
  while (i < str_len) {
    if (str[i] == ' ' || str[i] == '\0') {
      break;
    }
    i++;
  }
  return i;
}

bool words_match(char str_1[], int str1_start, int str1_end, char str_2[], int str_2_start, int str_2_end) {
  int str_len = str1_end - str1_start;
  int str_2_len = str_2_end - str_2_start;

  if (str_len != str_2_len) {
    return false;
  }

  int i = str1_start, j = str_2_start;
  while (i < str1_end && j < str_2_end) {
    if (str_1[i] != str_2[j]) {
      return false;
    }
    i++;
    j++;
  }

  // printf("Match found: ");
  // print_by_index(str_1, str1_start, str1_end);
  return true;
}

void truncate_from_to(char src[], int start_index, int end_index) {
  int src_len = str_len(src);
  int i = start_index;
  int j = end_index;

  while (j < src_len) {
    src[i] = src[j];
    i++;
    j++;
  }

  src[i] = '\0';
}

int delete_words(char src[], char pattern[]) {
  printf("\n");

  int src_len = str_len(src);
  int pattern_len = str_len(pattern);

  int deletion_count = 0;
  int source_start = 0;

  while (source_start < src_len) {
    int src_word_start = source_start;
    int src_word_end = word_end_index(src, src_len, source_start);

    bool word_deleted = false;
    int pattern_start = 0;

    while (pattern_start < pattern_len) {
      int pattern_word_start = pattern_start;
      int pattern_word_end = word_end_index(pattern, pattern_len, pattern_start);

      bool match = words_match(src, src_word_start, src_word_end, pattern, pattern_word_start, pattern_word_end);

      if (match) {
        truncate_from_to(src, src_word_start, src_word_end + 1);

        deletion_count++;
        src_len = str_len(src);
        word_deleted = true;
        break;
      }

      pattern_start = pattern_word_end + 1;
    }

    if (!word_deleted) {
      source_start = src_word_end + 1;
    }
  }
  src_len = str_len(src);
  truncate_from_to(src, src_len - 1, src_len);

  return deletion_count;
}

int main(void) {

  char src[] = "ahoj svete ahoj ahoj test";
  char pattern[] = "ahoj test";

  // Test cases

  // char src[] = "aa bb cc";
  // char pattern[] = "bb";
  // "aa cc"

  // char src[] = "aa bb cc nejaka slova uprostred dd";
  // char pattern[] = "bb cc dd ahoj priklad slov";
  // "aa nejaka slova uprostred"

  // char src[] = "aa bb cc dd ee";
  // char pattern[] = "bb aa dd ee cc";
  // ""

  // char src[] = "aa bb cc dd";
  // char pattern[] = "ee ff gg hh";
  // "aa bb cc dd"

  // char src[] = "";
  // char pattern[] = "a b c d";
  // ""

  // char src[] = "aa bb cc dd";
  // char pattern[] = "";
  // ""

  printf("Source string:\n");
  print_by_index(src, 0, str_len(src));
  printf("Pattern:\n");
  print_by_index(pattern, 0, str_len(pattern));

  int deletion_count = delete_words(src, pattern);

  switch (deletion_count) {
  case 0:
    printf("No words deleted\n");
    printf("Unchanged string:\n");
    print_by_index(src, 0, str_len(src));
    break;
  case 1:
    printf("Changed after 1 deletion:\n");
    print_by_index(src, 0, str_len(src));
    break;
  default:
    printf("Changed after %i deletions:\n", deletion_count);
    print_by_index(src, 0, str_len(src));
    break;
  }
}

// Konya

// Expected output
/*
Source string:
"ahoj svete ahoj ahoj test"
Pattern:
"ahoj test"

Changed after 4 deletions:
"svete"
*/