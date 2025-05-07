#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T 3
#define MAX_VALUES (2 * T - 1)
#define MIN_VALUES (T - 1)
#define MAX_CHILDREN (2 * T)

typedef struct B {
  int values[MAX_VALUES];
  int value_count;

  struct B *children[MAX_CHILDREN];
  int children_count;

  bool is_leaf;
} B;

int max(int a, int b) { return (a > b) ? a : b; }

B *createNode(void) {
  B *node = (B *)malloc(sizeof(B));
  node->value_count = 0;
  node->children_count = 0;
  node->is_leaf = true;
  for (int i = 0; i < MAX_CHILDREN; i++)
    node->children[i] = NULL;
  return node;
}

void freeNode(B *node) {
  if (!node)
    return;
  for (int i = 0; i < node->children_count; i++) {
    freeNode(node->children[i]);
  }
  free(node);
}

int getHeight(B *node) {
  if (!node)
    return 0;
  if (node->is_leaf)
    return 1;
  return 1 + getHeight(node->children[0]);
}

B *insertSplit(B *node, int value) {
  // TODO

  return node;
}

B *insertValue(B *node, int value) {
  // TODO

  return node;
}

B *insertNode(B *root, int value) {
  if (!root) {
    root = createNode();
    root->values[0] = value;
    root->value_count = 1;
    return root;
  }

  bool is_full = root->value_count == MAX_VALUES;

  if (is_full) {
    root = insertSplit(root, value);
    return root;

  } else {
    root = insertValue(root, value);
    return root;
  }
}

B *search(B *node, int value) {
  if (!node)
    return NULL;
  int i = 0;
  while (i < node->value_count && value > node->values[i])
    i++;
  if (i < node->value_count && node->values[i] == value)
    return node;
  if (node->is_leaf)
    return NULL;
  return search(node->children[i], value);
}

void inorder(B *node) {
  if (!node)
    return;
  for (int i = 0; i < node->value_count; i++) {
    if (!node->is_leaf)
      inorder(node->children[i]);
    printf("%d ", node->values[i]);
  }
  if (!node->is_leaf)
    inorder(node->children[node->value_count]);
}

void print_array(int a[], int a_len) {
  printf("[");
  for (int i = 0; i < a_len; i++) {
    printf("%i", a[i]);
    if (i < a_len - 1)
      printf(", ");
  }
  printf("]\n");
}

void print_root(B *node) {
  if (!node)
    return;
  print_array(node->values, node->value_count);
}

void print_children(B *node) {
  if (!node)
    return;
  for (int i = 0; i < node->children_count; i++) {
    printf("%d: ", i);
    print_array(node->children[i]->values, node->children[i]->value_count);
  }
}

int main(void) {
  B *root = NULL;

  root = insertNode(root, 10);
  root = insertNode(root, 20);
  root = insertNode(root, 5);
  root = insertNode(root, 6);
  root = insertNode(root, 12);
  root = insertNode(root, 30);
  root = insertNode(root, 7);
  root = insertNode(root, 17);
  root = insertNode(root, 50);
  root = insertNode(root, 66);

  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  printf("Root height: %d\n", getHeight(root));
  printf("Root values:\n");
  print_root(root);
  printf("\n");

  printf("Children values:\n");
  print_children(root);
  printf("\n");

  freeNode(root);
  return 0;
}
