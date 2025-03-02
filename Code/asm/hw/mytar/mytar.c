#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  INVALID,
  LIST,
  CAT,
} OPERATION;

#define TAR_BLOCK_SIZE 512

void usage(void) {
  printf("Usage:\n");
  printf("\tmytar --list <tar>\n");
  printf("\tmytar -l <tar>\n");
  printf("\tmytar --cat <tar> <filename>\n");
  printf("\tmytar -x <tar> <filename>\n");
}

int list_files(FILE *tar_file) {
  char header[TAR_BLOCK_SIZE];
  size_t bytes_read;

  while ((bytes_read = fread(header, 1, TAR_BLOCK_SIZE, tar_file)) ==
         TAR_BLOCK_SIZE) {
    // If empty - end of archive.
    if (header[0] == '\0') break;

    // File name from the header.
    printf("%s\n", header);

    // Skip file data by file size, rounded to a tar block size.
    long file_size = strtol(&header[124], NULL, 8);

    long padding;

    if (file_size % TAR_BLOCK_SIZE == 0) {
      padding = 0;
    } else {
      padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
    }

    fseek(tar_file, (file_size + padding), SEEK_CUR);
  }

  return EXIT_SUCCESS;
}

int cat_file(FILE *tar_file, char *contained_file) {
  char header[TAR_BLOCK_SIZE];
  size_t bytes_read;

  while ((bytes_read = fread(header, 1, TAR_BLOCK_SIZE, tar_file)) ==
         TAR_BLOCK_SIZE) {
    // If empty - end of archive.
    if (header[0] == '\0') break;

    // If filename matches search, print contents.
    if (!strcmp(header, contained_file)) {
      long file_size = strtol(&header[124], NULL, 8);

      char *content = malloc(file_size + 1);
      if (content == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
      }

      // Read file contents into buffer
      fread(content, 1, file_size, tar_file);

      // Don't print final newline
      content[file_size - 1] = '\0';

      // Print file contents
      printf("%s\n", content);

      return EXIT_SUCCESS;
    }

    // Skip file data by file size, rounded to a tar block size.
    long file_size = strtol(&header[124], NULL, 8);

    long padding;

    if (file_size % TAR_BLOCK_SIZE == 0) {
      padding = 0;
    } else {
      padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
    }

    fseek(tar_file, file_size + padding, SEEK_CUR);
  }

  // If file is not found - print error message.
  printf("File not found: %s\n", contained_file);
  return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
  char *tar_name = NULL;
  char *file_name = NULL;
  FILE *tar = NULL;

  OPERATION operation = INVALID;

  if (argc == 1) {
    usage();
    return EXIT_FAILURE;
  } else if (argc == 3 &&
             (!strcmp(argv[1], "--list") || !strcmp(argv[1], "-l"))) {
    operation = LIST;
    tar_name = argv[2];
  } else if (argc == 4 &&
             (!strcmp(argv[1], "--cat") || !strcmp(argv[1], "-x"))) {
    operation = CAT;
    tar_name = argv[2];
    file_name = argv[3];
  } else {
    operation = INVALID;
  }

  switch (operation) {
    case LIST: {
      tar = fopen(tar_name, "r");

      if (!tar) {
        fprintf(stderr, "Unable to open tar file.\n\n");
        usage();
        return EXIT_FAILURE;
      }

      list_files(tar);
      fclose(tar);
      break;
    }

    case CAT: {
      tar = fopen(tar_name, "r");

      if (!tar) {
        fprintf(stderr, "Unable to open tar file.\n\n");
        usage();
        return EXIT_FAILURE;
      }

      cat_file(tar, file_name);
      fclose(tar);
      break;
    }
    case INVALID: {
      printf("Invalid syntax\n");

      usage();
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

// Konya

// Expected output:
/*
➜ ./mytar.exe
Usage:
  mytar --list <tar>
  mytar -l <tar>
  mytar --cat <tar> <filename>
  mytar -x <tar> <filename>

➜ ./mytar.exe -l foo.tar
baz.dat
bar.dat

➜ ./mytar.exe -x foo.tar bar.dat
Test 1 2 3

➜ ./mytar.exe wrong_syntax
Usage:
  mytar --list <tar>
  mytar -l <tar>
  mytar --cat <tar> <filename>
  mytar -x <tar> <filename>

*/
