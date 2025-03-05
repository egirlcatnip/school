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
  printf("\tmytar --cat <tar> [<filename> ...]\n");
  printf("\tmytar -x <tar> [<filename> ...]\n");
}

int list_files(FILE* tar_file) {
  char header[TAR_BLOCK_SIZE];
  char file_name[FILE_NAME_SIZE + 1];

  // List all files in the tar_file
  while (fread(header, 1, TAR_BLOCK_SIZE, tar_file) == TAR_BLOCK_SIZE) {
    // If "\0" -  end of tar
    if (header[0] == '\0')
      break;

    // Get file size from header (OCT)
    long file_size = strtol(&header[124], NULL, 8);

    // Extract file_name (first 100B)
    memcpy(file_name, header, FILE_NAME_SIZE);
    file_name[FILE_NAME_SIZE] = '\0';
    printf("%s\n", file_name);

    // Padding - file_size + padding = 512B
    long padding;
    if (file_size % TAR_BLOCK_SIZE) {
      padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
    } else {
      padding = 0;
    }

    // Skip to next block (every 512B)
    fseek(tar_file, file_size + padding, SEEK_CUR);
  }

  return EXIT_SUCCESS;
}

int cat_files(FILE* tar_file, int requested_count, char* requested_files[]) {
  char header[TAR_BLOCK_SIZE];
  char file_name[FILE_NAME_SIZE + 1];
  bool file_found = false;
  bool all_files_found = true;

  if (!requested_count) {
    // Cat all files in the tar_file
    while (fread(header, 1, TAR_BLOCK_SIZE, tar_file) == TAR_BLOCK_SIZE) {
      // If "\0" - end of tar
      if (header[0] == '\0')
        break;

      // Get file size from header (OCT)
      long file_size = strtol(&header[124], NULL, 8);

      char* content = malloc(file_size + 1);
      if (!content) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
      }

      /*
      // Extract file_name (first 100B)
      memcpy(file_name, header, FILE_NAME_SIZE);
      file_name[FILE_NAME_SIZE] = '\0';
      printf("%s: ", file_name);
      */

      // Read contents into buffer
      fread(content, 1, file_size, tar_file);
      content[file_size - 1] = '\0';
      printf("%s\n", content);

      free(content);

      // Padding - file_size + padding = 512B
      long padding;
      if (file_size % TAR_BLOCK_SIZE) {
        padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
      } else {
        padding = 0;
      }

      // Skip to next block (every 512B)
      fseek(tar_file, padding, SEEK_CUR);
    }
  }

  else {
    // Cat specific files
    for (int i = 0; i < requested_count; i++) {
      rewind(tar_file);
      file_found = false;

      while (fread(header, 1, TAR_BLOCK_SIZE, tar_file) == TAR_BLOCK_SIZE) {
        // If empty - end of archive.
        if (header[0] == '\0')
          break;

        // Extract file_name (first 100B)
        memcpy(file_name, header, FILE_NAME_SIZE);
        file_name[FILE_NAME_SIZE] = '\0';

        // Compare with the requested filename
        if (!strcmp(file_name, requested_files[i])) {
          long file_size = strtol(&header[124], NULL, 8);

          char* content = malloc(file_size + 1);
          if (!content) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
          }

          /*
          // Print file_name disabled by default
          printf("%s: ", file_name);
          */

          // Read contents into the buffer
          fread(content, 1, file_size, tar_file);
          content[file_size - 1] = '\0';
          printf("%s\n", content);

          free(content);

          file_found = true;

          break;
        }

        // Get file size from header (OCT)
        long file_size = strtol(&header[124], NULL, 8);

        // Padding - file_size + padding = 512B
        long padding;
        if (file_size % TAR_BLOCK_SIZE != 0) {
          padding = TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE);
        } else {
          padding = 0;
        }

        // Skip to next block (every 512B)
        fseek(tar_file, file_size + padding, SEEK_CUR);
      }

      if (!file_found) {
        printf("File not found: `%s`\n", requested_files[i]);
        all_files_found = false;
      }
    }
  }

  if (!all_files_found) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  char* tar_name = NULL;
  FILE* tar = NULL;
  OPERATION operation = INVALID;

  if (argc == 1) {
    usage();
    return EXIT_SUCCESS;
  }

  // Get operation
  else if (argc == 3 &&
           (!strcmp(argv[1], "-l") || (!strcmp(argv[1], "--list")))) {
    operation = LIST;
    tar_name = argv[2];
  }

  else if (argc >= 3 &&
           (!strcmp(argv[1], "-x") || (!strcmp(argv[1], "--cat")))) {
    operation = CAT;
    tar_name = argv[2];
  }

  else {
    operation = INVALID;
  }

  // Perform operation
  switch (operation) {
    case INVALID: {
      printf("Invalid syntax\n");
      usage();
      exit(EXIT_FAILURE);
    }

    case LIST: {
      tar = fopen(tar_name, "rb");
      if (!tar) {
        fprintf(stderr, "Invalid tar file name.\n");
        usage();
        return EXIT_FAILURE;
      }

      if (list_files(tar)) {
        return EXIT_FAILURE;
      };

      fclose(tar);
      break;
    }

    case CAT: {
      tar = fopen(tar_name, "rb");
      if (!tar) {
        fclose(tar);
        fprintf(stderr, "Unable to open `%s`.\n\n", tar_name);
        usage();
        return EXIT_FAILURE;
      }

      int file_count = argc - 3;
      char** files = &argv[3];

      if (cat_files(tar, file_count, files)) {
        return EXIT_FAILURE;
      };

      fclose(tar);
      break;
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
        mytar --cat <tar> [<filename> ...]
        mytar -x <tar> [<filename> ...]

➜ mytar -l foo.tar
baz.dat
bar.dat

➜ mytar -x foo.tar
Test 1 2 3
Test 4 5 6
Test 7 8 9

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
