#include "avl_tree.h"
#include <stdio.h>

int main(void) {
  AVL *root = NULL;
  root = insert(root, 10, 100);
  root = insert(root, 20, 200);
  root = insert(root, 30, 300);
  root = insert(root, 40, 400);
  root = insert(root, 50, 500);
  root = insert(root, 25, 250);

  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  AVL *found = search(root, 25);
  if (found)
    printf("Found key 25 with value %d\n", found->value);
  else
    printf("Key 25 not found\n");

  printf("Deleting key 20\n");
  root = deleteNode(root, 20);

  printf("Inorder traversal after deletion:\n");
  inorder(root);
  printf("\n");

  freeTree(root);
  return 0;
}
