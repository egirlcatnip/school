#include <stdio.h>

void print_by_index(char str[], int index_start, int index_end) {
  for (int i = index_start; i < index_end; i++) {
    printf("%c", str[i]);
  }
}

void print_spaces(int len) {
  for (int i = 0; i < len; i++) {
    printf(" ");
  }
}

int str_len(char str[]) {
  int str_len = 0;
  while (str[str_len] != '\0') {
    str_len++;
  }
  return str_len;
}

void spacer(int line_len) {
  printf("\n");
  for (int i = 0; i <= line_len; i++) {
    printf("-");
  }
  printf("\n");
}

void remove_duplicate_whitespace(char src[], int src_len) {
  int j = 0;
  int space_found = 0;
  int i = 0;

  // Skip leading spaces
  while (i < src_len && (src[i] == ' ' || src[i] == '\n')) {
    i++;
  }

  for (; i < src_len; i++) {
    if (src[i] != ' ' && src[i] != '\n') {
      src[j++] = src[i];
      space_found = 0;
    } else if (!space_found) {
      src[j++] = ' ';
      space_found = 1;
    }
  }

  // Remove trailing space
  if (src[j - 1] == ' ') {
    j--;
  }

  src[j] = '\0'; // Null-terminate the cleaned string
}

int word_end_index(char src[], int src_len, int starting_index) {
  int i = starting_index + 1;

  while (i < src_len) {
    if (src[i] == ' ' || src[i] == '\n' || src[i] == '\0') {
      break;
    }
    i++;
  }

  return i - starting_index;
}

void justify_left(char src[], int line_len) {
  printf("justify_left():");
  spacer(line_len);
  int src_len = str_len(src);

  remove_duplicate_whitespace(src, src_len);
  // Recalculate src_len after removing duplicate whitespace
  src_len = str_len(src);

  int start = 0;

  while (start < src_len) {
    int chars_used = 0;

    // Calculate how many characters fit in the current line
    while (start + chars_used < src_len && chars_used < line_len) {
      int word_len = word_end_index(src, src_len, start + chars_used);
      if (word_len > line_len) {
        printf("word_len can't be longer than the line_len!!!");
        return;
      }

      if (chars_used + word_len > line_len) {
        break;
      }
      chars_used += word_len;
    }

    print_by_index(src, start, start + chars_used);
    printf("\n");

    // Move to the next line
    start += chars_used;

    // Skip any leading whitespace for the next line
    while (start < src_len && (src[start] == ' ' || src[start] == '\n')) {
      start++;
    }
  }

  spacer(line_len);
  return;
}

void justify_right(char src[], int line_len) {
  printf("justify_right():");
  spacer(line_len);
  int src_len = str_len(src);

  remove_duplicate_whitespace(src, src_len);
  src_len = str_len(src);
  // Recalculate src_len after removing duplicate whitespace

  int start = 0;

  while (start < src_len) {
    int chars_used = 0;

    // Calculate how many characters fit in the current line
    while (start + chars_used < src_len && chars_used < line_len) {
      int word_len = word_end_index(src, src_len, start + chars_used);
      if (word_len > line_len) {
        printf("word_len can't be longer than the line_len!!!");
        return;
      }
      if (chars_used + word_len > line_len) {
        break;
      }
      chars_used += word_len;
    }

    print_spaces(line_len - chars_used + 1);
    print_by_index(src, start, start + chars_used);
    printf("\n");

    // Move to the next line
    start += chars_used;

    // Skip any leading whitespace for the next line
    while (start < src_len && (src[start] == ' ' || src[start] == '\n')) {
      start++;
    }
  }

  spacer(line_len);
  return;
}

int main(void) {
  char src[] = "vzorovy \n text   ukazuje priklad zarovnani textu ";

  // Testing
  // char src[] = "  \n  test  \n  ";
  // char src[] = "t";
  // char src[] = "veryveryvery veryveryvery veryveryvery long"
  // char src[] = "veryveryveryveryveryveryveryveryveryvery long";

  int line_len = 30;
  int src_len = str_len(src);

  // Checks
  if (line_len <= 0) {
    printf("line_len is too short");
    return 1;
  }
  if (src_len <= 0) {
    printf("string is too short");
    return 1;
  }

  printf("String:");
  spacer(line_len);
  print_by_index(src, 0, src_len);
  spacer(line_len);

  printf("\n");
  justify_left(src, line_len);

  printf("\n");
  justify_right(src, line_len);

  return 0;
}

/*
Konya

String:
-------------------------------
vzorovy
 text   ukazuje priklad zarovnani textu
-------------------------------

justify_left():
-------------------------------
vzorovy text ukazuje priklad
zarovnani textu

-------------------------------

justify_right():
-------------------------------
   vzorovy text ukazuje priklad
                zarovnani textu

-------------------------------

*/
