#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RNB {
  int value;
  Color color;
  struct RNB *left;
  struct RNB *right;
  struct RNB *parent;
} RNB;

RNB *createNode(int value) {
  RNB *node = (RNB *)malloc(sizeof(RNB));
  node->value = value;
  node->color = RED;
  node->left = node->right = node->parent = NULL;
  return node;
}

void freeNode(RNB *node) {
  if (!node)
    return;
  freeNode(node->left);
  freeNode(node->right);
  free(node);
}

RNB *minRNB(RNB *node) {
  while (node && node->left)
    node = node->left;
  return node;
}

void rotateLeft(RNB **root, RNB *x) {
  RNB *y = x->right;
  x->right = y->left;
  if (y->left)
    y->left->parent = x;
  y->parent = x->parent;
  if (!x->parent)
    *root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void rotateRight(RNB **root, RNB *y) {
  RNB *x = y->left;
  y->left = x->right;
  if (x->right)
    x->right->parent = y;
  x->parent = y->parent;
  if (!y->parent)
    *root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  x->right = y;
  y->parent = x;
}

void fixInsert(RNB **root, RNB *z) {
  while (z->parent && z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      RNB *y = z->parent->parent->right;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(root, z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateRight(root, z->parent->parent);
      }
    } else {
      RNB *y = z->parent->parent->left;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(root, z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateLeft(root, z->parent->parent);
      }
    }
  }
  (*root)->color = BLACK;
}

void insertNode(RNB **root, int value) {
  RNB *z = createNode(value);
  RNB *y = NULL;
  RNB *x = *root;

  while (x) {
    y = x;
    if (value < x->value)
      x = x->left;
    else if (value > x->value)
      x = x->right;
    else {
      free(z);
      return;
    } // Duplicate
  }

  z->parent = y;
  if (!y)
    *root = z;
  else if (value < y->value)
    y->left = z;
  else
    y->right = z;

  fixInsert(root, z);
}

void transplant(RNB **root, RNB *u, RNB *v) {
  if (!u->parent)
    *root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v)
    v->parent = u->parent;
}

void fixDelete(RNB **root, RNB *x) {
  while (x != *root && x && x->color == BLACK) {
    if (x == x->parent->left) {
      RNB *w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(root, x->parent);
        w = x->parent->right;
      }
      if ((!w->left || w->left->color == BLACK) &&
          (!w->right || w->right->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      } else {
        if (!w->right || w->right->color == BLACK) {
          if (w->left)
            w->left->color = BLACK;
          w->color = RED;
          rotateRight(root, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w->right)
          w->right->color = BLACK;
        rotateLeft(root, x->parent);
        x = *root;
      }
    } else {
      RNB *w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateRight(root, x->parent);
        w = x->parent->left;
      }
      if ((!w->left || w->left->color == BLACK) &&
          (!w->right || w->right->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      } else {
        if (!w->left || w->left->color == BLACK) {
          if (w->right)
            w->right->color = BLACK;
          w->color = RED;
          rotateLeft(root, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w->left)
          w->left->color = BLACK;
        rotateRight(root, x->parent);
        x = *root;
      }
    }
  }
  if (x)
    x->color = BLACK;
}

void deleteNode(RNB **root, int value) {
  RNB *z = *root;
  while (z) {
    if (value == z->value)
      break;
    if (value < z->value)
      z = z->left;
    else
      z = z->right;
  }
  if (!z)
    return;

  RNB *y = z;
  Color yOriginalColor = y->color;
  RNB *x;

  if (!z->left) {
    x = z->right;
    transplant(root, z, z->right);
  } else if (!z->right) {
    x = z->left;
    transplant(root, z, z->left);
  } else {
    y = minRNB(z->right);
    yOriginalColor = y->color;
    x = y->right;
    if (y->parent == z) {
      if (x)
        x->parent = y;
    } else {
      transplant(root, y, x);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  free(z);
  if (yOriginalColor == BLACK)
    fixDelete(root, x);
}

RNB *search(RNB *node, int value) {
  if (!node || node->value == value)
    return node;
  if (value < node->value)
    return search(node->left, value);
  return search(node->right, value);
}

void inorder(RNB *node) {
  if (!node)
    return;
  inorder(node->left);
  printf("%d ", node->value);
  inorder(node->right);
}

int main(void) {
  RNB *root = NULL;
  insertNode(&root, 10);
  insertNode(&root, 20);
  insertNode(&root, 30);
  insertNode(&root, 15);
  insertNode(&root, 25);
  insertNode(&root, 5);

  printf("Inorder traversal: ");
  inorder(root);
  printf("\n");

  printf("Deleting node with value 20\n");
  deleteNode(&root, 20);

  printf("Inorder traversal after deletion: ");
  inorder(root);
  printf("\n");

  freeNode(root);
  return 0;
}
