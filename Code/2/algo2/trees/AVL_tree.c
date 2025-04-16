#include <stdio.h>
#include <stdlib.h>

typedef struct AVL {
  int value;
  int height;
  struct AVL *left;
  struct AVL *right;
} AVL;

int max(int a, int b) { return (a > b) ? a : b; }

AVL *createNode(int value) {
  AVL *node = (AVL *)malloc(sizeof(AVL));
  node->value = value;
  node->left = node->right = NULL;
  node->height = 1;
  return node;
}

void freeNode(AVL *node) {
  if (!node)
    return;
  freeNode(node->left);
  freeNode(node->right);
  free(node);
}

int getHeight(AVL *node) {
  if (!node)
    return 0;
  return node->height;
}

int getBalance(AVL *node) {
  if (!node)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

AVL *minAVL(AVL *node) {
  while (node && node->left)
    node = node->left;
  return node;
}

AVL *rotateRight(AVL *y) {
  AVL *x = y->left;
  AVL *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  return x;
}

AVL *rotateLeft(AVL *x) {
  AVL *y = x->right;
  AVL *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  return y;
}

AVL *insertNode(AVL *node, int value) {
  if (!node)
    return createNode(value);
  if (value < node->value)
    node->left = insertNode(node->left, value);
  else if (value > node->value)
    node->right = insertNode(node->right, value);
  else
    return node;

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  if (balance > 1 && value < node->left->value)
    return rotateRight(node);
  if (balance < -1 && value > node->right->value)
    return rotateLeft(node);
  if (balance > 1 && value > node->left->value) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && value < node->right->value) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

AVL *deleteNode(AVL *node, int value) {
  if (!node)
    return node;
  if (value < node->value)
    node->left = deleteNode(node->left, value);
  else if (value > node->value)
    node->right = deleteNode(node->right, value);
  else {
    if (!node->left || !node->right) {
      AVL *temp = node->left ? node->left : node->right;
      if (!temp) {
        free(node);
        return NULL;
      } else {
        *node = *temp;
        free(temp);
      }
    } else {
      AVL *temp = minAVL(node->right);
      node->value = temp->value;
      node->right = deleteNode(node->right, temp->value);
    }
  }

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  if (balance > 1 && getBalance(node->left) >= 0)
    return rotateRight(node);
  if (balance > 1 && getBalance(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && getBalance(node->right) <= 0)
    return rotateLeft(node);
  if (balance < -1 && getBalance(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

AVL *search(AVL *node, int value) {
  if (!node || node->value == value)
    return node;
  if (value < node->value)
    return search(node->left, value);
  return search(node->right, value);
}

void inorder(AVL *node) {
  if (!node)
    return;
  inorder(node->left);
  printf("%d ", node->value);
  inorder(node->right);
}

int main(void) {
  AVL *root = NULL;
  root = insertNode(root, 10);
  root = insertNode(root, 20);
  root = insertNode(root, 30);
  root = insertNode(root, 40);
  root = insertNode(root, 50);
  root = insertNode(root, 25);

  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  printf("Deleting node with value 20\n");
  root = deleteNode(root, 20);

  printf("Inorder traversal after deletion:\n");
  inorder(root);
  printf("\n");

  freeNode(root);
  return 0;
}
