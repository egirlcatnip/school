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

// Function to print a substring and its indices
void print_word(char src[], int index_start, int length) {
  for (int i = index_start; i < index_start + length; i++) {
    printf("%c", src[i]);
  }
  printf(" <%d,%d>\n", index_start, index_start + length - 1);
}

// Search function to find all substrings that match the pattern
void search(char src[], char pattern[], int src_len, int pattern_len) {
  for (int i = 0; i <= src_len - pattern_len; i++) {
    int current_len = 0;

    // Match pattern with the substring starting from index i
    for (int j = 0; j < pattern_len && (i + j) < src_len; j++) {
      if (src[i + j] == pattern[j]) {
        current_len++;
      } else {
        break;
      }
    }

    // If a match was found, print it and update the best match if necessary
    if (current_len > 0) {
      print_word(src, i, current_len);
    }

    // Update best match if this is the longest match so far
    if (current_len > best_len) {
      best_len = current_len;
      best_index = i;
    }
  }
}

int main(void) {
  // Test string and pattern
  char src[] = "ahoj svete ah";
  char pattern[] = "ahojte";

  int src_len = str_len(src);
  int pattern_len = str_len(pattern);

  // Checks for invalid input sizes
  if (src_len <= 0) {
    printf("String must be of size larger than 0\n");
    return 1;
  }
  if (pattern_len <= 0) {
    printf("Pattern must be of size larger than 0\n");
    return 1;
  }

  // Print the strings being compared
  printf("String: \"%s\"\n", src);
  printf("Looking for: \"%s\"\n", pattern);

  // Call search to find matching substrings
  search(src, pattern, src_len, pattern_len);

  // Print the best match if any
  if (best_len > 0) {
    printf("\n");
    printf("Found at index %i with len %i\n", best_index, best_len);
    print_word(src, best_index, best_len);
  } else {
    printf("\nNo matches found\n");
  }

  return 0;
}

// Konya

/*
String: "ahoj svete ah"
Looking for: "ahojte"
ahoj <0,3>
ah <11,12>

Found at index 0 with len 4
ahoj <0,3>
*/
