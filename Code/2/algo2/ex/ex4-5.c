#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWEST_BRANCH_SPACING 3
#define HORIZONTAL_GAP 10

//===========================
// Binary Tree Structure
//===========================
typedef struct BinaryTree {
  int value;
  struct BinaryTree *left;
  struct BinaryTree *right;
} BinaryTree;

//===========================
// Binary Tree Functions
//===========================

// Creates a new tree node
BinaryTree *create_tree(int value) {
  BinaryTree *node = (BinaryTree *)malloc(sizeof(BinaryTree));
  if (!node) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Frees the allocated tree memory
void free_tree(BinaryTree *t) {
  if (!t)
    return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}

// Appends a child node to the left of the parent
BinaryTree *append_tree_left(BinaryTree *parent, BinaryTree *child) {
  if (parent)
    parent->left = child;
  return child;
}

// Appends a child node to the right of the parent
BinaryTree *append_tree_right(BinaryTree *parent, BinaryTree *child) {
  if (parent)
    parent->right = child;
  return child;
}

//---------------------------
// Rotation Functions
//---------------------------

// Rotates a tree left at the given node pointer (pointer-to-pointer version)
void rotate_tree_left(BinaryTree **root) {
  if (!root || !*root || !(*root)->right)
    return;
  BinaryTree *new_root = (*root)->right;
  (*root)->right = new_root->left;
  new_root->left = *root;
  *root = new_root;
}

// Rotates a tree right at the given node pointer (pointer-to-pointer version)
void rotate_tree_right(BinaryTree **root) {
  if (!root || !*root || !(*root)->left)
    return;
  BinaryTree *new_root = (*root)->left;
  (*root)->left = new_root->right;
  new_root->right = *root;
  *root = new_root;
}

// Rotates a tree left and returns the new root (using a tree pointer)
BinaryTree *rotate_left(BinaryTree *root) {
  if (!root || !root->right)
    return root;
  BinaryTree *new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;
  return new_root;
}

// Rotates a tree right and returns the new root (using a tree pointer)
BinaryTree *rotate_right(BinaryTree *root) {
  if (!root || !root->left)
    return root;
  BinaryTree *new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

//---------------------------
// Removal Functions
//---------------------------

// Removes an entire subtree and frees its memory.
// This function sets *root to NULL.
int remove_tree(BinaryTree **root) {
  if (!root || !*root)
    return 1;
  free_tree(*root);
  *root = NULL;
  return 0;
}

// Removes the first node with the given value (preorder search).
// Returns 1 if a node was removed, 0 otherwise.
int remove_tree_by_value(BinaryTree **root, int value) {
  if (!root || !*root)
    return 0;
  if ((*root)->value == value) {
    remove_tree(root);
    return 1;
  }
  if (remove_tree_by_value(&((*root)->left), value))
    return 1;
  if (remove_tree_by_value(&((*root)->right), value))
    return 1;
  return 0;
}

//---------------------------
// Value-Based Rotation Functions
//---------------------------

// Recursively rotates the node with the given value left using rotate_left.
void rotate_tree_left_by_value(BinaryTree **root, int value) {
  if (!root || !*root)
    return;
  if ((*root)->value == value) {
    *root = rotate_left(*root);
    return;
  }
  rotate_tree_left_by_value(&((*root)->left), value);
  rotate_tree_left_by_value(&((*root)->right), value);
}

// Recursively rotates the node with the given value right using rotate_right.
void rotate_tree_right_by_value(BinaryTree **root, int value) {
  if (!root || !*root)
    return;
  if ((*root)->value == value) {
    *root = rotate_right(*root);
    return;
  }
  rotate_tree_right_by_value(&((*root)->left), value);
  rotate_tree_right_by_value(&((*root)->right), value);
}

//---------------------------
// Tree Visualization Helpers (Top-Down)
//---------------------------

// Returns the height of the binary tree
int get_tree_height(BinaryTree *t) {
  if (!t)
    return 0;
  int left_height = get_tree_height(t->left);
  int right_height = get_tree_height(t->right);
  return 1 + (left_height > right_height ? left_height : right_height);
}

// Computes the width of the tree visualization grid (top-down).
// This is based on the number of leaves and the spacing.
int get_tree_width(int height) {
  int leaves = 1 << (height - 1);
  return leaves + (leaves - 1) * LOWEST_BRANCH_SPACING;
}

// Places a node's value in the visualization grid.
// Only the first character of the number is displayed.
void place_value(char **grid, int row, int col, int value) {
  char buf[12]; // large enough for any 32-bit int
  snprintf(buf, sizeof(buf), "%d", value);
  int len = str_len(buf);

  // Place number centered around `col` if possible
  int start_col = col - len / 2;
  for (int i = 0; i < len; i++) {
    if (start_col + i >= 0) {
      grid[row][start_col + i] = buf[i];
    }
  }
}

// Recursively fills the grid with tree nodes and draws connector lines
// (top-down).
void fill_grid(BinaryTree *t, char **grid, int row, int col, int height,
               int level) {
  if (level >= height)
    return;
  if (!t) {
    grid[row][col] = '_';
    if (level < height - 1) {
      int offset =
          ((LOWEST_BRANCH_SPACING + 1) * (1 << (height - level - 2))) / 2;
      fill_grid(NULL, grid, row + 2, col - offset, height, level + 1);
      fill_grid(NULL, grid, row + 2, col + offset, height, level + 1);
    }
    return;
  }
  // Place the node's value.
  place_value(grid, row, col, t->value);
  if (level < height - 1) {
    int offset =
        ((LOWEST_BRANCH_SPACING + 1) * (1 << (height - level - 2))) / 2;
    if (t->left) {
      int left_connector = col - offset / 2;
      grid[row + 1][left_connector] = '/';
    }
    if (t->right) {
      int right_connector = col + offset / 2;
      grid[row + 1][right_connector] = '\\';
    }
    fill_grid(t->left, grid, row + 2, col - offset, height, level + 1);
    fill_grid(t->right, grid, row + 2, col + offset, height, level + 1);
  }
}

// Prints the binary tree graphically using a grid layout (top-down).
void print_tree(BinaryTree **t) {
  if (!t || !*t)
    return;
  int height = get_tree_height(*t);
  int width = get_tree_width(height);
  int grid_rows =
      height * 2 - 1; // Each level takes 2 rows except the last level.
  char **grid = (char **)calloc(grid_rows, sizeof(char *));
  for (int i = 0; i < grid_rows; i++) {
    grid[i] = (char *)calloc(width + 1, sizeof(char));
    memset(grid[i], ' ', width);
    grid[i][width] = '\0';
  }
  int center = width / 2;
  fill_grid(*t, grid, 0, center, height, 0);
  for (int i = 0; i < grid_rows; i++) {
    printf("%s\n", grid[i]);
  }
  for (int i = 0; i < grid_rows; i++)
    free(grid[i]);
  free(grid);
}

//---------------------------
// Additional Functions
//---------------------------

// Prints the tree in descending order
void print_tree_desc(BinaryTree *t) {
  if (!t)
    return;
  print_tree_desc(t->right);
  printf("%d ", t->value);
  print_tree_desc(t->left);
}

// Finds the minimum value in the tree
int find_min(BinaryTree *t) {
  if (!t)
    return -1; // Assuming all values are non-negative
  while (t->left)
    t = t->left;
  return t->value;
}

// Finds the maximum value in the tree
int find_max(BinaryTree *t) {
  if (!t)
    return -1; // Assuming all values are non-negative
  while (t->right)
    t = t->right;
  return t->value;
}

//---------------------------
// Sample Tree Construction
//---------------------------
/*
      0
    /   \
   1     2
  / \   / \
 3   4 5   6
*/
BinaryTree *binary_tree(void) {
  BinaryTree *root = create_tree(0);
  BinaryTree *leftChild = append_tree_left(root, create_tree(111));
  append_tree_left(leftChild, create_tree(3));
  append_tree_right(leftChild, create_tree(4));

  BinaryTree *rightChild = append_tree_right(root, create_tree(2));
  append_tree_left(rightChild, create_tree(5));
  append_tree_right(rightChild, create_tree(6));

  return root;
}

//---------------------------
// Main Function
//---------------------------
int main(void) {
  printf("Binary Tree\n");
  BinaryTree *bt = binary_tree();
  print_tree(&bt);

  printf("Tree height: %d\n", get_tree_height(bt));
  printf("Minimum value in the tree: %d\n", find_min(bt));
  printf("Maximum value in the tree: %d\n", find_max(bt));

  printf("\n");

  printf("Tree in descending order: ");
  print_tree_desc(bt);
  printf("\n");

  printf("\n");

  printf("Rotated node root left\n");
  rotate_tree_left(&bt);
  print_tree(&bt);

  printf("Tree in descending order: ");
  print_tree_desc(bt);
  printf("\n");
  printf("Unchanged, because rotation doesn't change the ordering\n");

  printf("\n");

  printf("Rotated node root->0 right by value\n");
  rotate_tree_right_by_value(&bt->left, 0);
  print_tree(&bt);

  printf("\n");

  printf("Removed node root->left->right\n");
  remove_tree(&bt->left->right);
  print_tree(&bt);

  printf("\n");

  printf("Removed node root->6 by value\n");
  remove_tree_by_value(&bt, 6);
  print_tree(&bt);

  printf("\n");

  printf("Removed node root->left->left\n");
  remove_tree(&bt->left->left);
  print_tree(&bt);

  free_tree(bt);
  return 0;
}

// Konya

// Expected output:
/*
Binary Tree
      0
    /   \
  1       2
 / \     / \
3   4   5   6

Tree height: 3
Minimum value in the tree: 3
Maximum value in the tree: 6

Tree in descending order: 6 2 5 0 4 1 3

Rotated node root left
              2
          /       \
      0               6
    /   \
  1       5       _       _
 / \
3   4   _   _   _   _   _   _

Tree in descending order: 6 2 5 0 4 1 3
Unchanged, because rotation doesn't change the ordering

Rotated node root->0 right by value
              2
          /       \
      1               6
    /   \
  3       0       _       _
         / \
_   _   4   5   _   _   _   _


Removed node root->left->right
      2
    /   \
  1       6
 /
3   _   _   _


Removed node root->6 by value
      2
    /
  1       _
 /
3   _   _   _


Removed node root->left->left
  2
 /
1   _
*/
