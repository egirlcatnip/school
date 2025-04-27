// pbm.c

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int width;
  int height;
  int *data;
} picture;

picture load_from_pbm(char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not open file %s\n", filename);
    exit(1);
  }

  char header[3];
  fscanf(file, "%2s", header);
  if (header[0] != 'P' || header[1] != '1') {
    fprintf(stderr, "Invalid PBM format `%s`\n", header);
    fclose(file);
    exit(1);
  }

  int width;
  int height;
  fscanf(file, "%d %d", &width, &height);

  if (width <= 0 || height <= 0) {
    fprintf(stderr, "Invalid dimensions: %dx%d\n", width, height);
    fclose(file);
    exit(1);
  }

  picture pict;
  pict.width = width;
  pict.height = height;
  pict.data = (int *)malloc(width * height * sizeof(int));
  if (!pict.data) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(file);
    exit(1);
  }

  for (int i = 0; i < width * height; i++) {
    fscanf(file, "%d", &pict.data[i]);
  }

  fclose(file);
  return pict;
}

void mirror_picture(picture *pict) {
  for (int y = 0; y < pict->height; y++) {
    for (int x = 0; x < pict->width / 2; x++) {
      int idx1 = y * pict->width + x;
      int idx2 = y * pict->width + (pict->width - 1 - x);
      int temp = pict->data[idx1];
      pict->data[idx1] = pict->data[idx2];
      pict->data[idx2] = temp;
    }
  }
}

void save_to_pbm(char *filename, picture src) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    fprintf(stderr, "Could not open file `%s`\n", filename);
    exit(1);
  }

  fprintf(file, "P1\n");
  fprintf(file, "%d %d\n", src.width, src.height);

  for (int y = 0; y < src.height; y++) {
    for (int x = 0; x < src.width; x++) {
      fprintf(file, "%d", src.data[y * src.width + x]);
      if (x < src.width - 1) {
        fprintf(file, " ");
      }
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

void print_picture(picture *pict) {
  for (int y = 0; y < pict->height; y++) {
    for (int x = 0; x < pict->width; x++) {
      printf("%d ", pict->data[y * pict->width + x]);
    }
    printf("\n");
  }
}

int main(void) {
  char *filename = "test.pbm";
  printf("Loading picture from `%s`...\n", filename);
  picture pict = load_from_pbm(filename);

  printf("Before mirroring:\n");
  print_picture(&pict);
  mirror_picture(&pict);

  printf("\n");

  printf("After mirroring:\n");
  print_picture(&pict);

  printf("\n");

  char *output_filename = filename;
  printf("Saving picture to `%s`...\n", output_filename);
  save_to_pbm(output_filename, pict);

  printf("Picture saved successfully.\n");
  free(pict.data);
  return 0;
}

// Konya

/*
Loading picture from `test.pbm`...
Before mirroring:
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
1 0 0 0 1 0
0 1 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0

After mirroring:
0 1 0 0 0 0
0 1 0 0 0 0
0 1 0 0 0 0
0 1 0 0 0 0
0 1 0 0 0 0
0 1 0 0 0 0
0 1 0 0 0 1
0 0 1 1 1 0
0 0 0 0 0 0
0 0 0 0 0 0

Saving picture to `test.pbm`...
Picture saved successfully.
*/
