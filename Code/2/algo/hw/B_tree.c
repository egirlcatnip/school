#include <stdio.h>
#include <stdlib.h>

#define T int

typedef struct BTreeNode {
  T value;
  struct BTreeNode *left, *right;
} BTreeNode;

BTreeNode *createNode(T value) {
  BTreeNode *node = malloc(sizeof(BTreeNode));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BTreeNode *insert(BTreeNode *root, T value) {
  if (root == NULL)
    return createNode(value);
  if (value < root->value)
    root->left = insert(root->left, value);
  else if (value > root->value)
    root->right = insert(root->right, value);
  return root;
}

BTreeNode *findMin(BTreeNode *node) {
  while (node->left != NULL)
    node = node->left;
  return node;
}

BTreeNode *deleteNode(BTreeNode *root, T value) {
  if (root == NULL)
    return NULL;
  if (value < root->value)
    root->left = deleteNode(root->left, value);
  else if (value > root->value)
    root->right = deleteNode(root->right, value);
  else {
    if (root->left == NULL) {
      BTreeNode *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      BTreeNode *temp = root->left;
      free(root);
      return temp;
    } else {
      BTreeNode *temp = findMin(root->right);
      root->value = temp->value;
      root->right = deleteNode(root->right, temp->value);
    }
  }
  return root;
}

void inorder(BTreeNode *root) {
  if (root == NULL)
    return;
  inorder(root->left);
  printf("%d ", root->value);
  inorder(root->right);
}

void freeNode(BTreeNode *root) {
  if (root == NULL)
    return;
  freeNode(root->left);
  freeNode(root->right);
  free(root);
}

int main(void) {
  BTreeNode *root = NULL;

  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 5);
  root = insert(root, 6);
  root = insert(root, 12);
  root = insert(root, 30);
  root = insert(root, 7);
  root = insert(root, 17);
  root = insert(root, 50);
  root = insert(root, 66);

  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  root = deleteNode(root, 20);
  root = deleteNode(root, 10);
  root = deleteNode(root, 7);

  printf("After deletions:\n");
  inorder(root);
  printf("\n");

  freeNode(root);
  return 0;
}
