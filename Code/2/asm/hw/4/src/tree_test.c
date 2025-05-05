#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for rand()
#include <time.h>   // Include time.h for time()

int random_int(int min, int max) { return (rand() % (max - min + 1)) + min; }

AVL *fill_tree(AVL *root, int count) {
  for (int i = 0; i < count; i++) {
    int key = random_int(1, 1000000);
    int value = random_int(1, 10000);
    root = insert(root, key, value);
  }
  return root;
}

int main(void) {
  int seed = 1;

  if (seed == 0)
    seed = time(NULL);

  printf("Random seed: %d\n", seed);
  srand(seed);

  AVL *root = NULL;
  int number = 1000000;

  printf("Filling tree with %d nodes...\n", number);
  root = fill_tree(root, number);

  printf("Height of the tree: %d\n", getHeight(root));

  // Test the search function
  int search_key = random_int(1, 1000000);
  printf("Searching for key %d...\n", search_key);
  AVL *search_result = search(root, search_key);

  if (search_result != NULL) {
    printf("Found key %d with value %d\n", search_key, search_result->value);
  } else {
    printf("Key %d not found in the tree\n", search_key);
  }

  freeTree(root);
  return 0;
}
