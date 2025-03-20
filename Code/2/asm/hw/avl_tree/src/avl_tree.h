#ifndef MATRIX_H
#define MATRIX_H

typedef struct AVLNode {
  int key;
  int height;
  struct AVLNode *left;
  struct AVLNode *right;
} AVLNode;

AVLNode *create_node(int key);
int height(AVLNode *node);
AVLNode *right_rotate(AVLNode *y);
AVLNode *left_rotate(AVLNode *x);
int get_balance(AVLNode *node);
AVLNode *insert_node(AVLNode *node, int key);
void inorder_traversal(AVLNode *root);
void free_tree(AVLNode *root);

#endif
