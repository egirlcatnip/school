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

void usage(void) {
  printf("Usage:\n");
  printf("\tmytar --list <tar>\n");
  printf("\tmytar -l <tar>\n");
  printf("\tmytar --cat <tar> <filename> [<filename> ...]\n");
  printf("\tmytar -x <tar> <filename> [<filename> ...]\n");
}

int list_files(FILE *tar_file) {
  char header[TAR_BLOCK_SIZE];
  size_t bytes_read;

  while ((bytes_read = fread(header, 1, TAR_BLOCK_SIZE, tar_file)) ==
         TAR_BLOCK_SIZE) {
    // If empty - end of archive.
    if (header[0] == '\0')
      break;

    // File name from the header.
    printf("%s\n", header);

    // Skip file data by file size, rounded to a tar block size.
    long file_size = strtol(&header[124], NULL, 8);

    long padding;

    if (file_size % TAR_BLOCK_SIZE == 0) {
      padding = 0;
    }
    else {
      padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
    }

    fseek(tar_file, (file_size + padding), SEEK_CUR);
  }

  return EXIT_SUCCESS;
}

int cat_files(FILE *tar_file, int file_count, char *contained_files[]) {
  char header[TAR_BLOCK_SIZE];
  size_t bytes_read;

  for (int i = 0; i < file_count; i++) {
    // Reset file pointer to the beginning for each file
    rewind(tar_file);
    bool found = false;

    while ((bytes_read = fread(header, 1, TAR_BLOCK_SIZE, tar_file)) ==
           TAR_BLOCK_SIZE) {
      // If empty - end of archive.
      if (header[0] == '\0')
        break;

      // If filename matches search, print contents.
      if (!strcmp(header, contained_files[i])) {
        long file_size = strtol(&header[124], NULL, 8);

        char *content = malloc(file_size);
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

        free(content);
        found = true;
        break;
      }

      // Skip file data by file size, rounded to a tar block size.
      long file_size = strtol(&header[124], NULL, 8);

      long padding;

      if (file_size % TAR_BLOCK_SIZE == 0) {
        padding = 0;
      }
      else {
        padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
      }

      fseek(tar_file, file_size + padding, SEEK_CUR);
    }

    if (!found) {
      printf("File not found: `%s`\n", contained_files[i]);
    }
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  char *tar_name = NULL;
  FILE *tar = NULL;

  OPERATION operation = INVALID;

  if (argc == 1) {
    usage();
    return EXIT_SUCCESS;
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
    case LIST: {
      tar = fopen(tar_name, "r");

      if (!tar) {
        fprintf(stderr, "Unable to open file `%s`.\n\n", tar_name);
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
        fprintf(stderr, "Unable to open `%s`.\n\n", tar_name);
        usage();
        return EXIT_FAILURE;
      }

      cat_files(tar, argc - 3, &argv[3]);
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
File not found: `invalid.dat`

Usage:
        mytar --list <tar>
        mytar -l <tar>
        mytar --cat <tar> <filename> [<filename> ...]
        mytar -x <tar> <filename> [<filename> ...]


*/
