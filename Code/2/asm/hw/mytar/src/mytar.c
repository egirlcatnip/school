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

typedef struct {
  char name[100];     // File name
  char mode[8];       // File mode
  char uid[8];        // Owner's numeric user ID
  char gid[8];        // Group's numeric user ID
  char size[12];      // File size in bytes (octal)
  char mtime[12];     // Last modification time (octal)
  char checksum[8];   // Checksum for header (octal)
  char typeflag[1];   // Type flag
  char linkname[100]; // Name of linked file
  char magic[6];      // Magic "ustar"
  char version[3];    // Version "00"
  char uname[33];     // Owner user name
  char gname[33];     // Owner group name
  char devmajor[8];   // Device major number (octal)
  char devminor[8];   // Device minor number (octal)
  char prefix[155];   // Prefix for file names longer than 100 bytes
  long parsed_size;   // Parsed file size from 'size' field
} TarEntry;

typedef struct {
  FILE *file; // File pointer to the tar archive
} TarArchive;

static long compute_padding(long file_size) {
  return (TAR_BLOCK_SIZE - (file_size % TAR_BLOCK_SIZE)) % TAR_BLOCK_SIZE;
}

static int tar_read_next_entry(TarArchive *archive, TarEntry *entry) {
  char header[TAR_BLOCK_SIZE];
  if (fread(header, 1, TAR_BLOCK_SIZE, archive->file) != TAR_BLOCK_SIZE) {
    return 0;
  }

  if (header[0] == '\0') {
    return 0;
  }

  // Copy and null-terminate fields
  memcpy(entry->name, header, 100);
  entry->name[99] = '\0';

  memcpy(entry->mode, header + 100, 8);
  entry->mode[7] = '\0';

  memcpy(entry->uid, header + 108, 8);
  entry->uid[7] = '\0';

  memcpy(entry->gid, header + 116, 8);
  entry->gid[7] = '\0';

  memcpy(entry->size, header + 124, 12);
  entry->size[11] = '\0';
  entry->parsed_size = strtol(entry->size, NULL, 8);

  memcpy(entry->mtime, header + 136, 12);
  entry->mtime[11] = '\0';

  memcpy(entry->checksum, header + 148, 8);
  entry->checksum[7] = '\0';

  memcpy(entry->typeflag, header + 156, 1);
  entry->typeflag[0] = '\0';

  memcpy(entry->linkname, header + 157, 100);
  entry->linkname[99] = '\0';

  memcpy(entry->magic, header + 257, 6);
  entry->magic[5] = '\0';

  memcpy(entry->version, header + 263, 2);
  entry->version[2] = '\0';

  memcpy(entry->uname, header + 265, 32);
  entry->uname[32] = '\0';

  memcpy(entry->gname, header + 297, 32);
  entry->gname[32] = '\0';

  memcpy(entry->devmajor, header + 329, 8);
  entry->devmajor[7] = '\0';

  memcpy(entry->devminor, header + 337, 8);
  entry->devminor[7] = '\0';

  memcpy(entry->prefix, header + 345, 155);
  entry->prefix[154] = '\0';

  return 1;
}

static void tar_skip_entry_data(TarArchive *archive, long file_size) {
  long padding = compute_padding(file_size);
  fseek(archive->file, file_size + padding, SEEK_CUR);
}

TarArchive *tar_open(const char *filename, const char *mode) {
  TarArchive *archive = malloc(sizeof(TarArchive));
  if (!archive) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  archive->file = fopen(filename, mode);
  if (!archive->file) {
    fprintf(stderr, "Unable to open file: %s\n", filename);
    free(archive);
    return NULL;
  }

  TarEntry entry;
  if (!tar_read_next_entry(archive, &entry) ||
      strcmp(entry.magic, "ustar") != 0) {
    fprintf(stderr, "Not a valid tar archive: `%s`\n", filename);

    fclose(archive->file);
    free(archive);
    return NULL;
  }

  rewind(archive->file);
  return archive;
}

void tar_close(TarArchive *archive) {
  if (archive) {
    fclose(archive->file);
    free(archive);
  }
}

void usage(void) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  mytar --list <tar>\n");
  fprintf(stderr, "  mytar -l <tar>\n");
  fprintf(stderr, "  mytar --cat <tar> [<filename> ...]\n");
  fprintf(stderr, "  mytar -x <tar> [<filename> ...]\n");
}

int list_files(TarArchive *archive) {
  TarEntry entry;

  while (tar_read_next_entry(archive, &entry)) {
    fprintf(stdout, "%s\n", entry.name);
    tar_skip_entry_data(archive, entry.parsed_size);
  }

  return EXIT_SUCCESS;
}

int cat_files(TarArchive *archive, int requested_count,
              char *requested_files[]) {
  TarEntry entry;
  bool all_files_found = true;

  if (requested_count == 0) {
    while (tar_read_next_entry(archive, &entry)) {
      char *content = malloc(entry.parsed_size + 1);
      if (!content) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
      }
      if (fread(content, 1, entry.parsed_size, archive->file) !=
          (size_t)entry.parsed_size) {
        fprintf(stderr, "Error reading file content\n");
        free(content);
        exit(EXIT_FAILURE);
      }
      content[entry.parsed_size] = '\0';
      fprintf(stdout, "%s", content);
      free(content);

      long padding = compute_padding(entry.parsed_size);
      fseek(archive->file, padding, SEEK_CUR);
    }
  } else {
    for (int i = 0; i < requested_count; i++) {
      rewind(archive->file);
      bool file_found = false;

      while (tar_read_next_entry(archive, &entry)) {
        if (strcmp(entry.name, requested_files[i]) == 0) {
          char *content = malloc(entry.parsed_size + 1);
          if (!content) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          if (fread(content, 1, entry.parsed_size, archive->file) !=
              (size_t)entry.parsed_size) {
            fprintf(stderr, "Error reading file content\n");
            free(content);
            exit(EXIT_FAILURE);
          }
          content[entry.parsed_size] = '\0';
          fprintf(stdout, "%s", content);
          free(content);
          file_found = true;

          long padding = compute_padding(entry.parsed_size);
          fseek(archive->file, padding, SEEK_CUR);
          break;
        } else {
          tar_skip_entry_data(archive, entry.parsed_size);
        }
      }

      if (!file_found) {
        fprintf(stderr, "File not found: `%s`\n", requested_files[i]);
        all_files_found = false;
      }
    }
  }

  return all_files_found ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
  char *tar_name = NULL;
  TarArchive *archive = NULL;
  OPERATION operation = INVALID;

  if (argc == 1) {
    usage();
    return EXIT_SUCCESS;
  } else if (argc == 3 &&
             (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--list"))) {
    operation = LIST;
    tar_name = argv[2];
  } else if (argc >= 3 &&
             (!strcmp(argv[1], "-x") || !strcmp(argv[1], "--cat"))) {
    operation = CAT;
    tar_name = argv[2];
  } else {
    operation = INVALID;
  }

  if (operation == INVALID) {
    fprintf(stderr, "Invalid syntax `");
    for (int i = 1; i < argc; i++) {
      fprintf(stderr, "%s", argv[i]);
      if (i < argc - 1) {
        fprintf(stderr, " ");
      }
    }
    fprintf(stderr, "`\n\n");
    usage();
    return EXIT_FAILURE;
  }

  archive = tar_open(tar_name, "rb");
  if (!archive) {
    return EXIT_FAILURE;
  }

  int result = (operation == LIST) ? list_files(archive)
                                   : cat_files(archive, argc - 3, &argv[3]);
  tar_close(archive);
  return result;
}
