#include <stdio.h>
#include <stdlib.h>

typedef struct AVL {
  int key;
  int value;
  int height;
  struct AVL *left;
  struct AVL *right;
} AVL;

int max(int a, int b);

AVL *createNode(int key, int value);

void freeTree(AVL *node);

int getHeight(AVL *node);

int getBalance(AVL *node);

AVL *rotateRight(AVL *y);

AVL *rotateLeft(AVL *x);

AVL *insert(AVL *node, int key, int value);

AVL *minNode(AVL *node);

AVL *deleteNode(AVL *node, int key);

AVL *search(AVL *node, int key);

void inorder(AVL *node);
