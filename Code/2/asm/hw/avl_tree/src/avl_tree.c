#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return (a > b) ? a : b; }

int height(AVLNode *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

AVLNode *create_node(int key) {
  AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
  node->key = key;
  node->left = node->right = NULL;
  node->height = 1;
  return node;
}

AVLNode *right_rotate(AVLNode *y) {
  AVLNode *x = y->left;
  AVLNode *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

AVLNode *left_rotate(AVLNode *x) {
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

int get_balance(AVLNode *node) {
  if (node == NULL)
    return 0;
  return height(node->left) - height(node->right);
}

AVLNode *insert_node(AVLNode *node, int key) {
  if (node == NULL)
    return create_node(key);

  if (key < node->key)
    node->left = insert_node(node->left, key);
  else if (key > node->key)
    node->right = insert_node(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = get_balance(node);
  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return right_rotate(node);
  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return left_rotate(node);
  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = left_rotate(node->left);
    return right_rotate(node);
  }
  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = right_rotate(node->right);
    return left_rotate(node);
  }

  return node;
}

void inorder_traversal(AVLNode *root) {
  if (root != NULL) {
    inorder_traversal(root->left);
    printf("%d ", root->key);
    inorder_traversal(root->right);
  }
}

void free_tree(AVLNode *root) {
  if (root) {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}
