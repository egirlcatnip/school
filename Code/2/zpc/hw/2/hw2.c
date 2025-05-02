#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RLE_encode(char *in_path, char *out_path) {
  FILE *in_file = fopen(in_path, "rb");
  if (!in_file) {
    fprintf(stderr, "Error opening input file `%s`.\n", in_path);
    return EXIT_FAILURE;
  }

  FILE *out_file = fopen(out_path, "wb");
  if (!out_file) {
    fclose(in_file);
    fprintf(stderr, "Error opening output file `%s`.\n", out_path);
    return EXIT_FAILURE;
  }

  int prev = fgetc(in_file);
  if (prev == EOF) {
    fclose(in_file);
    fclose(out_file);
    return EXIT_FAILURE;
  }

  int count = 1;
  int curr = 0;
  while ((curr = fgetc(in_file)) != EOF) {
    if (curr == prev) {
      count++;
    } else {
      while (count > 256) {
        fputc(prev, out_file);
        fputc(255, out_file);
        count -= 256;
      }
      fputc(prev, out_file);
      fputc(count - 1, out_file);
      prev = curr;
      count = 1;
    }
  }

  while (count > 256) {
    fputc(prev, out_file);
    fputc(255, out_file);
    count -= 256;
  }
  fputc(prev, out_file);
  fputc(count - 1, out_file);

  fclose(in_file);
  fclose(out_file);

  return EXIT_SUCCESS;
}

int RLE_decode(char *in_path, char *out_path) {
  FILE *in_file = fopen(in_path, "rb");
  if (!in_file) {
    fprintf(stderr, "Error opening input file `%s`.\n", in_path);
    return EXIT_FAILURE;
  }

  FILE *out_file = fopen(out_path, "wb");
  if (!out_file) {
    fclose(in_file);
    fprintf(stderr, "Error opening output file `%s`.\n", out_path);
    return EXIT_FAILURE;
  }

  int symbol = 0;
  int count = 1;
  while ((symbol = fgetc(in_file)) != EOF) {
    count = fgetc(in_file);
    if (count == EOF)
      break;
    for (int i = 0; i <= count; i++) {
      fputc(symbol, out_file);
    }
  }

  fclose(in_file);
  fclose(out_file);

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: hw2 <encode|decode> <input_file> <output_file>\n");
    return 1;
  }

  if (strcmp(argv[1], "encode") == 0) {
    return RLE_encode(argv[2], argv[3]);
  } else if (strcmp(argv[1], "decode") == 0) {
    return RLE_decode(argv[2], argv[3]);
  } else {
    printf("Invalid operation. Use 'encode' or 'decode'.\n");
    printf("Usage: hw2 <encode|decode> <input_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  return 0;
}
