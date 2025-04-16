#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct B {
  int keys[2 * T - 1];
  struct B *children[2 * T];
  int numKeys;
  int isLeaf;
} B;

B *createNode(int isLeaf) {
  B *node = malloc(sizeof(B));
  node->isLeaf = isLeaf;
  node->numKeys = 0;
  for (int i = 0; i < 2 * T - 1; i++)
    node->keys[i] = 0;
  for (int i = 0; i < 2 * T; i++)
    node->children[i] = NULL;
  return node;
}

void splitChild(B *parent, int i, B *child) {
  B *newChild = createNode(child->isLeaf);
  newChild->numKeys = T - 1;
  for (int j = 0; j < T - 1; j++)
    newChild->keys[j] = child->keys[j + T];
  if (!child->isLeaf)
    for (int j = 0; j < T; j++)
      newChild->children[j] = child->children[j + T];
  child->numKeys = T - 1;
  for (int j = parent->numKeys; j >= i + 1; j--)
    parent->children[j + 1] = parent->children[j];
  parent->children[i + 1] = newChild;
  for (int j = parent->numKeys - 1; j >= i; j--)
    parent->keys[j + 1] = parent->keys[j];
  parent->keys[i] = child->keys[T - 1];
  parent->numKeys++;
}

void insertNonFull(B *node, int key) {
  int i = node->numKeys - 1;
  if (node->isLeaf) {
    while (i >= 0 && key < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    if (i >= 0 && key == node->keys[i])
      return; // Skip duplicate
    node->keys[i + 1] = key;
    node->numKeys++;
  } else {
    while (i >= 0 && key < node->keys[i])
      i--;
    i++;
    if (node->children[i]->numKeys == 2 * T - 1) {
      splitChild(node, i, node->children[i]);
      if (key > node->keys[i])
        i++;
    }
    insertNonFull(node->children[i], key);
  }
}

void insert(B **root, int key) {
  B *r = *root;
  if (r->numKeys == 2 * T - 1) {
    B *s = createNode(0);
    if (!s)
      return;
    s->children[0] = r;
    *root = s;
    splitChild(s, 0, r);
    insertNonFull(s, key);
  } else {
    insertNonFull(r, key);
  }
}

void traverse(B *node) {
  if (!node)
    return;
  int i;
  for (i = 0; i < node->numKeys; i++) {
    if (!node->isLeaf)
      traverse(node->children[i]);
    printf("%d ", node->keys[i]);
  }
  if (!node->isLeaf)
    traverse(node->children[i]);
}

B *search(B *node, int key) {
  if (!node || node->numKeys == 0)
    return NULL;
  int i = 0;
  while (i < node->numKeys && key > node->keys[i])
    i++;
  if (i < node->numKeys && key == node->keys[i])
    return node;
  if (node->isLeaf)
    return NULL;
  return search(node->children[i], key);
}

void freeTree(B *node) {
  if (!node)
    return;
  if (!node->isLeaf)
    for (int i = 0; i <= node->numKeys; i++)
      if (node->children[i])
        freeTree(node->children[i]);
  free(node);
}

int main(void) {
  B *root = NULL;

  insert(&root, 10);
  insert(&root, 20);
  insert(&root, 5);
  insert(&root, 6);
  insert(&root, 12);
  insert(&root, 30);
  insert(&root, 7);
  insert(&root, 17);

  printf("B-Tree traversal: ");
  traverse(root);
  printf("\n");

  int key = 6;
  B *found = search(root, key);
  printf("Search for %d: %s\n", key, found ? "Found" : "Not found");

  freeTree(root);
  return 0;
}
