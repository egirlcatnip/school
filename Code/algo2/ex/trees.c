// Lecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWEST_BRANCH_SPACING 5

#if LOWEST_BRANCH_SPACING < 1
#undef LOWEST_BRANCH_SPACING
#define LOWEST_BRANCH_SPACING 1
#endif

//===========================
// Binary Tree (unchanged)
//===========================

typedef struct BinaryTree {
  int value;
  struct BinaryTree *left;
  struct BinaryTree *right;
} BinaryTree;

BinaryTree *create_binary_tree(int value) {
  BinaryTree *node = calloc(1, sizeof(BinaryTree));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BinaryTree *append_left(BinaryTree *parent, BinaryTree *child) {
  parent->left = child;
  return child;
}

BinaryTree *append_right(BinaryTree *parent, BinaryTree *child) {
  parent->right = child;
  return child;
}

int get_binary_tree_height(BinaryTree *t) {
  if (!t)
    return 0;
  int left_height = get_binary_tree_height(t->left);
  int right_height = get_binary_tree_height(t->right);
  return 1 + (left_height > right_height ? left_height : right_height);
}

int get_binary_tree_width(int height) {
  int leaves = 1 << (height - 1);
  return leaves + (leaves - 1) * LOWEST_BRANCH_SPACING;
}

void place_value(char **grid, int row, int col, int value) {
  char buf[10];
  sprintf(buf, "%d", value);
  grid[row][col] = buf[0];
}

// If a branch is missing, we put a placeholder ('_')
void fill_binary_tree_grid(BinaryTree *t, char **grid, int row, int col, int height, int level) {
  if (level >= height)
    return;
  if (!t) {
    grid[row][col] = '_';
    if (level < height - 1) {
      int offset = ((LOWEST_BRANCH_SPACING + 1) * (1 << (height - level - 2))) / 2;
      fill_binary_tree_grid(NULL, grid, row + 2, col - offset, height, level + 1);
      fill_binary_tree_grid(NULL, grid, row + 2, col + offset, height, level + 1);
    }
    return;
  }
  place_value(grid, row, col, t->value);
  if (level < height - 1) {
    int offset = ((LOWEST_BRANCH_SPACING + 1) * (1 << (height - level - 2))) / 2;
    fill_binary_tree_grid(t->left, grid, row + 2, col - offset, height, level + 1);
    fill_binary_tree_grid(t->right, grid, row + 2, col + offset, height, level + 1);
  }
}

void print_binary_tree_graph(BinaryTree *t) {
  if (!t)
    return;
  int height = get_binary_tree_height(t);
  int width = get_binary_tree_width(height);
  char **grid = calloc(height * 2, sizeof(char *));
  for (int i = 0; i < height * 2; i++) {
    grid[i] = calloc(width + 1, sizeof(char));
    memset(grid[i], ' ', width);
    grid[i][width] = '\0';
  }
  int center = width / 2;
  fill_binary_tree_grid(t, grid, 0, center, height, 0);
  for (int i = 0; i < height * 2; i += 2) {
    printf("%s\n\n", grid[i]);
  }
  for (int i = 0; i < height * 2; i++) {
    free(grid[i]);
  }
  free(grid);
}

//=============================
// Sample structures
//=============================

BinaryTree binary_tree(void) {
  BinaryTree *t = create_binary_tree(0);
  BinaryTree *t1 = append_left(t, create_binary_tree(1));
  BinaryTree *t3 = append_left(t1, create_binary_tree(3));
  append_left(t3, create_binary_tree(1));
  append_right(t3, create_binary_tree(2));
  // Missing right branch for t1
  BinaryTree *t2 = append_right(t, create_binary_tree(2));
  BinaryTree *t5 = append_left(t2, create_binary_tree(5));
  append_left(t5, create_binary_tree(5));
  append_right(t5, create_binary_tree(6));
  BinaryTree *t6 = append_right(t2, create_binary_tree(6));
  // Missing left branch for t6
  append_right(t6, create_binary_tree(8));
  return *t;
}

// Sample Binary Tree:
/*
                     0

         1                       2

   3           _           5           6

1     2     _     _     5     6     _     8
*/

int main(void) {
  printf("=== Binary Tree ===\n\n");
  BinaryTree bt = binary_tree();
  print_binary_tree_graph(&bt);

  printf("=== End ===\n");

  return 0;
}

// Konya

// Expected output:

/*
=== Binary Tree (Incomplete) Structure ===

                     0

         1                       2

   3           _           5           6

1     2     _     _     5     6     _     8

=== End ===
*/
