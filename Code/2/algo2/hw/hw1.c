#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTree {
  int key;
  int height;
  struct AVLTree *left;
  struct AVLTree *right;
} AVLTree;

int max(int a, int b) { return a > b ? a : b; }

int height(AVLTree *node) { return node ? node->height : 0; }

AVLTree *createNode(int key) {
  AVLTree *node = malloc(sizeof(AVLTree));
  node->key = key;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

AVLTree *rotateRight(AVLTree *y) {
  AVLTree *x = y->left;
  AVLTree *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVLTree *rotateLeft(AVLTree *x) {
  AVLTree *y = x->right;
  AVLTree *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

int getBalance(AVLTree *node) {
  return node ? height(node->left) - height(node->right) : 0;
}

AVLTree *insert(AVLTree *node, int key) {
  if (!node)
    return createNode(key);
  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  node->height = max(height(node->left), height(node->right)) + 1;
  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key)
    return rotateRight(node);
  if (balance < -1 && key > node->right->key)
    return rotateLeft(node);
  if (balance > 1 && key > node->left->key) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

AVLTree *minValueNode(AVLTree *node) {
  AVLTree *current = node;
  while (current->left)
    current = current->left;
  return current;
}

AVLTree *deleteNode(AVLTree *root, int key) {
  if (!root)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if (!root->left || !root->right) {
      AVLTree *temp = root->left ? root->left : root->right;
      if (!temp) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      AVLTree *temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (!root)
    return root;

  root->height = max(height(root->left), height(root->right)) + 1;
  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0)
    return rotateRight(root);
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0)
    return rotateLeft(root);
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}

void inorder(AVLTree *root) {
  if (root) {
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}

int main(void) {
  AVLTree *root = NULL;

  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 5);
  root = insert(root, 6);
  root = insert(root, 12);
  root = insert(root, 30);
  root = insert(root, 7);
  root = insert(root, 17);

  printf("Inorder:\n");
  inorder(root);
  printf("\n");

  printf("Removing 6...\n");
  root = deleteNode(root, 6);
  printf("Inorder:\n");
  inorder(root);
  printf("\n");

  printf("Removing 13...\n");
  root = deleteNode(root, 13);
  printf("Inorder:\n");
  inorder(root);
  printf("\n");

  return 0;
}
