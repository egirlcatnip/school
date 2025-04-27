#include <stdio.h>
#include <stdlib.h>

typedef struct BST {
  int value;
  struct BST *left;
  struct BST *right;
} BST;

BST *createNode(int value) {
  BST *node = (BST *)malloc(sizeof(BST));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void freeNode(BST *node) {
  if (!node)
    return;
  freeNode(node->left);
  freeNode(node->right);
  free(node);
}

int getHeight(BST *node) {
  if (!node)
    return 0;
  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getBalance(BST *node) {
  if (!node)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

BST *minBST(BST *node) {
  while (node && node->left)
    node = node->left;
  return node;
}

BST *maxBST(BST *node) {
  while (node && node->right)
    node = node->right;
  return node;
}

BST *rotateLeft(BST *node) {
  if (!node || !node->right)
    return node;
  BST *newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  return newRoot;
}

BST *rotateRight(BST *node) {
  if (!node || !node->left)
    return node;
  BST *newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  return newRoot;
}

BST *insertNode(BST *node, int value) {
  if (!node)
    return createNode(value);
  if (value < node->value)
    node->left = insertNode(node->left, value);
  else if (value > node->value)
    node->right = insertNode(node->right, value);
  return node;
}

BST *search(BST *node, int value) {
  if (!node) {
    return NULL;
  }

  if (node->value == value)
    return node;

  if (value < node->value)
    return search(node->left, value);
  return search(node->right, value);
}

BST *deleteNode(BST *node, int value) {
  if (!node)
    return NULL;
  if (value < node->value)
    node->left = deleteNode(node->left, value);
  else if (value > node->value)
    node->right = deleteNode(node->right, value);
  else {
    if (!node->left) {
      BST *right = node->right;
      free(node);
      return right;
    } else if (!node->right) {
      BST *left = node->left;
      free(node);
      return left;
    }
    BST *temp = minBST(node->right);
    node->value = temp->value;
    node->right = deleteNode(node->right, temp->value);
  }
  return node;
}

void inorder(BST *node) {
  if (!node)
    return;
  inorder(node->left);
  printf("%d ", node->value);
  inorder(node->right);
}

int main(void) {
  BST *root = NULL;
  root = insertNode(root, 10);
  root = insertNode(root, 20);
  root = insertNode(root, 30);
  root = insertNode(root, 40);
  root = insertNode(root, 50);
  root = insertNode(root, 25);

  printf("Inorder traversal: ");
  inorder(root);
  printf("\n");

  printf("Deleting node with value 20\n");
  root = deleteNode(root, 20);

  printf("Inorder traversal after deletion: ");
  inorder(root);
  printf("\n");

  freeNode(root);
}
