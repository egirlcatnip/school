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
    printf("%c", s.data[i]);
  }
}

void string_println(string s) {
  string_print(s);
  printf("\n");
}

string *split_string(string str, char delimiter, int *n) {
  int count = 1;
  for (size_t i = 0; i < str.len; i++) {
    if (str.data[i] == delimiter) {
      count++;
    }
  }

  string *result = malloc(count * sizeof(string));
  assert(result);

  size_t start = 0, index = 0;
  for (size_t i = 0; i <= str.len; i++) {
    if (i == str.len || str.data[i] == delimiter) {
      size_t length = i - start;
      result[index].len = length;
      result[index].data = malloc(length);
      assert(result[index].data);
      memcpy(result[index].data, str.data + start, length);
      start = i + 1;
      index++;
    }
  }
  *n = count;
  return result;
}

typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} string_builder;

void sb_allocate(string_builder *sb, size_t capacity) {
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

void sb_expand_if_needed(string_builder *sb, size_t additional) {
  if (sb->len + additional >= sb->capacity) {
    size_t new_capacity = (sb->capacity + additional) * 2;
    sb->data = realloc(sb->data, new_capacity);
    assert(sb->data);
    sb->capacity = new_capacity;
  }
}

void sb_print_int(string_builder *sb, int i) {
  char buffer[20];
  int length = snprintf(buffer, sizeof(buffer), "%d", i);
  sb_expand_if_needed(sb, length);
  memcpy(sb->data + sb->len, buffer, length);
  sb->len += length;
}

void sb_print_cstring(string_builder *sb, char *cs) {
  size_t length = strlen(cs);
  sb_expand_if_needed(sb, length);
  memcpy(sb->data + sb->len, cs, length);
  sb->len += length;
}

string sb_to_string(string_builder sb) {
  string result;
  result.len = sb.len;
  result.data = malloc(sb.len);
  assert(result.data);
  memcpy(result.data, sb.data, sb.len);
  return result;
}

int main(void) {
  string str = clone_from_cstring("ahoj--svete");
  int n = 0;
  char delimiter = '-';
  string *parts = split_string(str, delimiter, &n);

  printf("Parts of string: `");
  string_print(str);
  printf("` split by '%c' \n", delimiter);

  for (int i = 0; i < n; i++) {
    printf("\"");
    string_print(parts[i]);
    free(parts[i].data);
    printf("\"");
    printf("\n");
  }

  free(parts);
  free(str.data);

  printf("\n");

  printf("Testing string builder\n");

  string_builder sb = {0};
  sb_allocate(&sb, 5);
  sb_print_cstring(&sb, "test ");
  sb_print_int(&sb, -3);
  sb_print_cstring(&sb, " string builderu");

  string result = sb_to_string(sb);
  string_println(result);

  sb_destroy(&sb);
  free(result.data);
  return 0;
}
