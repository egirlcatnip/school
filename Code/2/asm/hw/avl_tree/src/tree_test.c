#include "avl_tree.h"
#include <stdio.h>

int main(void) {
  AVLNode *root = NULL;

  int keys[] = {20, 10, 30, 40, 50, 25};

  int n = sizeof(keys) / sizeof(keys[0]);

  for (int i = 0; i < n; i++) {
    root = insert_node(root, keys[i]);
  }

  printf("Inorder traversal of the constructed AVL tree:\n");
  inorder_traversal(root);
  printf("\n");

  free_tree(root);
  return 0;
}
