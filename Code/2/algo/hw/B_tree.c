#include <stdio.h>
#include <stdlib.h>

#define T 3;

typedef struct B {
  int value;
  struct B *left, *right;
} B;

int max(int a, int b) { return (a > b) ? a : b; }

B *createNode(int value) {
  B *node = (B *)malloc(sizeof(B));

  node->value = value;
  node->left = NULL;
  node->right = NULL;

  return node;
}

void freeNode(B *node) {
  if (!node)
    return;
  freeNode(node->left);
  freeNode(node->right);
  free(node);
}

int getHeight(B *node) {
  if (!node)
    return 0;
  return 1 + max(getHeight(node->left), getHeight(node->right));
}

int getBalance(B *node) {
  if (!node)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

B *insertNode(B *node, int value) {
  //
}

B *deleteNode(B *node, int value) {
  //
}

B *search(B *node, int value) {
  if (!node || node->value == value)
    return node;
  if (value < node->value)
    return search(node->left, value);
  return search(node->right, value);
}

void inorder(B *node) {
  if (node) {
    inorder(node->left);
    printf("%d ", node->value);
    inorder(node->right);
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

  printf("Deleting nodes with value 20:\n");
  root = deleteNode(root, 20);

  printf("Deleting nodes with value 10:\n");
  root = deleteNode(root, 10);

  printf("Deleting nodes with value 7:\n");
  root = deleteNode(root, 7);

  printf("Inorder traversal after deletion:\n");
  inorder(root);
  printf("\n");

  freeNode(root);
  return 0;
}

// Konya
