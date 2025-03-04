#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  INVALID,
  LIST,
  CAT,
} OPERATION;

#define TAR_BLOCK_SIZE 512
#define FILE_NAME_SIZE 100

void usage(void) {
  printf("Usage:\n");
  printf("\tmytar --list <tar>\n");
  printf("\tmytar -l <tar>\n");
  printf("\tmytar --cat <tar> <filename> [<filename> ...]\n");
  printf("\tmytar -x <tar> <filename> [<filename> ...]\n");
}

int list_files(FILE *tar_file) {
  char header[TAR_BLOCK_SIZE];
  char file_name[FILE_NAME_SIZE + 1];  // Extra byte for null terminator

  while (fread(header, 1, TAR_BLOCK_SIZE, tar_file) == TAR_BLOCK_SIZE) {
    // If empty - end of archive.
    if (header[0] == '\0') {
      break;
    }

    // Extract filename (first 100 bytes) and ensure null-termination
    memcpy(file_name, header, FILE_NAME_SIZE);
    file_name[FILE_NAME_SIZE] = '\0';

    // Print file name
    printf("%s\n", file_name);

    // Get file size from header (stored as octal)
    long file_size = strtol(&header[124], NULL, 8);

    // Calculate padding to maintain TAR block alignment
    long padding;
    if (file_size % TAR_BLOCK_SIZE) {
      padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
    }
    else {
      padding = 0;
    }

    // Skip to next block (every 512B)
    fseek(tar_file, file_size + padding, SEEK_CUR);
  }

  fclose(tar_file);
  return EXIT_SUCCESS;
}

int cat_files(FILE *tar_file, int file_count, char *contained_files[]) {
  char header[TAR_BLOCK_SIZE];
  char file_name[FILE_NAME_SIZE + 1];  // Null-terminated filename
  bool found = false;

  for (int i = 0; i < file_count; i++) {
    rewind(tar_file);
    found = false;

    while (fread(header, 1, TAR_BLOCK_SIZE, tar_file) == TAR_BLOCK_SIZE) {
      // If empty - end of archive.
      if (header[0] == '\0') {
        break;
      }

      // Extract filename
      memcpy(file_name, header, FILE_NAME_SIZE);
      file_name[FILE_NAME_SIZE] = '\0';

      // Compare with the requested filename
      if (!strcmp(file_name, contained_files[i])) {
        long packed_size = strtol(&header[124], NULL, 8);

        // Allocate memory for file content
        char *content =
            malloc(packed_size + 1);  // Extra byte for null terminator
        if (!content) {
          fprintf(stderr, "Memory allocation failed.\n");
          exit(EXIT_FAILURE);
        }

        // Read file contents into buffer
        fread(content, 1, packed_size, tar_file);
        content[packed_size - 1] = '\0';  // Null-terminate without nenwline

        // Print file contents
        printf("%s\n", content);

        free(content);
        found = true;
        break;
      }

      // Get file size and calculate padding
      long file_size = strtol(&header[124], NULL, 8);
      long padding;

      if (file_size % TAR_BLOCK_SIZE) {
        padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
      }
      else {
        padding = 0;
      }

      // Skip to next block (every 512B)
      fseek(tar_file, file_size + padding, SEEK_CUR);
    }

    if (!found) {
      printf("File not found: `%s`\n", contained_files[i]);
    }
  }

  fclose(tar_file);

  if (!found) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  char *tar_name = NULL;
  FILE *tar = NULL;
  OPERATION operation = INVALID;

  if (argc == 1) {
    usage();
    exit(EXIT_SUCCESS);
  }
  else if (argc == 3 &&
           (!strcmp(argv[1], "--list") || !strcmp(argv[1], "-l"))) {
    operation = LIST;
    tar_name = argv[2];
  }
  else if (argc >= 4 && (!strcmp(argv[1], "--cat") || !strcmp(argv[1], "-x"))) {
    operation = CAT;
    tar_name = argv[2];
  }
  else {
    operation = INVALID;
  }

  switch (operation) {
    case INVALID: {
      printf("Invalid syntax\n");
      usage();
      exit(EXIT_FAILURE);
    }

    case LIST: {
      tar = fopen(tar_name, "rb");
      if (!tar) {
        fprintf(stderr, "Unable to open file `%s`.\n\n", tar_name);
        usage();
        exit(EXIT_FAILURE);
      }

      if (list_files(tar)) {
        exit(EXIT_FAILURE);
      };
      break;
    }

    case CAT: {
      tar = fopen(tar_name, "rb");
      if (!tar) {
        fprintf(stderr, "Unable to open `%s`.\n\n", tar_name);
        usage();
        exit(EXIT_FAILURE);
      }

      if (cat_files(tar, argc - 3, &argv[3])) {
        exit(EXIT_FAILURE);
      };
      break;
    }
  }

  exit(EXIT_SUCCESS);
}

// Konya

// Expected output:

/*
➜ mytar
Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]

➜ mytar -l foo.tar
baz.dat
bar.dat

➜ mytar -x foo.tar bar.dat baz.dat
Test 1 2 3
Test 4 5 6

➜ mytar -l invalid_tar_file
Unable to open file `invalid_tar_file`.

➜ mytar invalid_syntax
Invalid syntax
Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]

➜ ./mytar.exe -x foo.tar invalid.dat
File not found: invalid.dat

Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]


*/