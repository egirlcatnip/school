#include "avl_tree.h"

int max(int a, int b) { return a > b ? a : b; }

AVL *createNode(int key, int value) {
  AVL *node = (AVL *)malloc(sizeof(AVL));
  node->key = key;
  node->value = value;
  node->height = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void freeTree(AVL *node) {
  if (!node)
    return;
  freeTree(node->left);
  freeTree(node->right);
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

AVL *insert(AVL *node, int key, int value) {
  if (!node)
    return createNode(key, value);
  if (key < node->key)
    node->left = insert(node->left, key, value);
  else if (key > node->key)
    node->right = insert(node->right, key, value);
  else {
    node->value = value;
    return node;
  }
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
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

AVL *minNode(AVL *node) {
  AVL *current = node;
  while (current->left)
    current = current->left;
  return current;
}

AVL *deleteNode(AVL *node, int key) {
  if (!node)
    return node;
  if (key < node->key)
    node->left = deleteNode(node->left, key);
  else if (key > node->key)
    node->right = deleteNode(node->right, key);
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
      AVL *temp = minNode(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = deleteNode(node->right, temp->key);
    }
  }
  if (!node)
    return node;
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

AVL *search(AVL *node, int key) {
  if (!node || node->key == key)
    return node;
  if (key < node->key)
    return search(node->left, key);
  return search(node->right, key);
}

void inorder(AVL *node) {
  if (!node)
    return;
  inorder(node->left);
  printf("(%d:%d) ", node->key, node->value);
  inorder(node->right);
}
