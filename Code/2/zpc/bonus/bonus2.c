#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t len;
} string;

string clone_from_cstring(char *cstring) {
  string ret = {0};
  ret.len = strlen(cstring);
  if (ret.len == 0) {
    ret.data = 0;
  } else {
    ret.data = malloc(ret.len);
    assert(ret.data);

    memcpy(ret.data, cstring, ret.len);
  }
  return ret;
}

void string_print(string s) {
  for (size_t i = 0; i < s.len; i++) {
    putchar(s.data[i]);
  }
}

void string_println(string s) {
  string_print(s);
  putchar('\n');
}

// Part 1: Split string
string *split_string(string str, char delimiter, int *n) {
  int substr_count = 1;
  for (size_t i = 0; i < str.len; i++) {
    if (str.data[i] == delimiter) {
      substr_count++;
    }
  }

  string *res = malloc(substr_count * sizeof(string));
  assert(res);

  size_t substr_start = 0;
  size_t substr_index = 0;

  for (size_t i = 0; i <= str.len; i++) {
    if (i == str.len || str.data[i] == delimiter) {
      size_t substr_len = i - substr_start;
      res[substr_index].len = substr_len;
      res[substr_index].data = malloc(substr_len);
      assert(res[substr_index].data);

      char *substr = str.data + substr_start;
      memcpy(res[substr_index].data, substr, substr_len);
      substr_start = i + 1;
      substr_index++;
    }
  }
  *n = substr_count;
  return res;
}

void print_array_of_strings(string *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("\"");
    string_print(arr[i]);
    printf("\"\n");
  }
}

// Part 2: String builder
typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} string_builder;

void sb_allocate(string_builder *sb, size_t capacity) {
  assert(capacity > 0);

  sb->data = malloc(capacity);
  assert(sb->data);

  sb->capacity = capacity;
  sb->len = 0;
}

void sb_destroy(string_builder *sb) {
  free(sb->data);
  sb->data = NULL;
  sb->capacity = 0;
  sb->len = 0;
}

int digit_count(int i) {
  int count = 0;
  if (i == 0) {
    return 1;
  }
  while (i != 0) {
    i /= 10;
    count++;
  }
  return count;
}

void sb_print_int(string_builder *sb, int num) {
  char buffer[20];
  int length = 0;

  if (num < 0) {
    buffer[0] = '-';
    length++;
    num = -num;
  }

  int num_digits = digit_count(num);

  for (int i = num_digits - 1; i >= 0; i--) {
    buffer[length + i] = '0' + (num % 10);
    num /= 10;
  }
  length += num_digits;

  assert(sb->len + length < sb->capacity);

  memcpy(sb->data + sb->len, buffer, length);
  sb->len += length;
}

size_t cstring_length(char *cstring) {
  size_t len = 0;
  while (cstring[len] != '\0') {
    len++;
  }

  return len;
}

void sb_print_cstring(string_builder *sb, char *cs) {
  size_t length = cstring_length(cs);
  assert(sb->len + length < sb->capacity);

  memcpy(sb->data + sb->len, cs, length);
  sb->len += length;
}

string sb_to_string(string_builder sb) {
  string res;
  res.len = sb.len;
  res.data = malloc(sb.len);
  assert(res.data);

  memcpy(res.data, sb.data, sb.len);

  return res;
}

int main(void) {
  string str;

  str = clone_from_cstring("ahoj--svete");
  int n = 0;
  char delimiter = '-';

  string *parts = split_string(str, delimiter, &n);

  printf("Parts of string: `");
  string_print(str);
  printf("` split by '%c' \n", delimiter);

  print_array_of_strings(parts, n);

  free(parts);
  free(str.data);

  printf("\n");

  printf("Testing string builder\n");

  string_builder sb;
  sb_allocate(&sb, 24); // "test -3 string builderu" + '\0'
  sb_print_cstring(&sb, "test ");
  sb_print_int(&sb, -3);
  sb_print_cstring(&sb, " string builderu");

  str = sb_to_string(sb);
  sb_destroy(&sb);

  string_println(str);
  free(str.data);

  return 0;
}

// Konya

/*
Parts of string: `ahoj--svete` split by '-'
"ahoj"
""
"svete"

Testing string builder
test -3 string builderu
*/
