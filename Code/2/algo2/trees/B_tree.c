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
  B *node = (B *)malloc(sizeof(B));
  node->isLeaf = isLeaf;
  node->numKeys = 0;
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
      return;
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
  if (!*root) {
    *root = createNode(1);
    (*root)->keys[0] = key;
    (*root)->numKeys = 1;
    return;
  }
  B *r = *root;
  if (r->numKeys == 2 * T - 1) {
    B *s = createNode(0);
    s->children[0] = r;
    *root = s;
    splitChild(s, 0, r);
    insertNonFull(s, key);
  } else {
    insertNonFull(r, key);
  }
}

int findKey(B *node, int key) {
  int idx = 0;
  while (idx < node->numKeys && node->keys[idx] < key)
    idx++;
  return idx;
}

void borrowFromPrev(B *node, int idx) {
  B *child = node->children[idx];
  B *sibling = node->children[idx - 1];
  for (int i = child->numKeys - 1; i >= 0; i--)
    child->keys[i + 1] = child->keys[i];
  if (!child->isLeaf)
    for (int i = child->numKeys; i >= 0; i--)
      child->children[i + 1] = child->children[i];
  child->keys[0] = node->keys[idx - 1];
  if (!child->isLeaf)
    child->children[0] = sibling->children[sibling->numKeys];
  node->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
  child->numKeys++;
  sibling->numKeys--;
}

void borrowFromNext(B *node, int idx) {
  B *child = node->children[idx];
  B *sibling = node->children[idx + 1];
  child->keys[child->numKeys] = node->keys[idx];
  if (!child->isLeaf)
    child->children[child->numKeys + 1] = sibling->children[0];
  node->keys[idx] = sibling->keys[0];
  for (int i = 1; i < sibling->numKeys; i++)
    sibling->keys[i - 1] = sibling->keys[i];
  if (!sibling->isLeaf)
    for (int i = 1; i <= sibling->numKeys; i++)
      sibling->children[i - 1] = sibling->children[i];
  child->numKeys++;
  sibling->numKeys--;
}

B *merge(B *node, int idx) {
  B *child = node->children[idx];
  B *sibling = node->children[idx + 1];
  child->keys[T - 1] = node->keys[idx];
  for (int i = 0; i < sibling->numKeys; i++)
    child->keys[i + T] = sibling->keys[i];
  if (!child->isLeaf)
    for (int i = 0; i <= sibling->numKeys; i++)
      child->children[i + T] = sibling->children[i];
  for (int i = idx + 1; i < node->numKeys; i++)
    node->keys[i - 1] = node->keys[i];
  for (int i = idx + 2; i <= node->numKeys; i++)
    node->children[i - 1] = node->children[i];
  child->numKeys += sibling->numKeys + 1;
  node->numKeys--;
  free(sibling);
  return child;
}

void fill(B *node, int idx) {
  if (idx != 0 && node->children[idx - 1]->numKeys >= T)
    borrowFromPrev(node, idx);
  else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= T)
    borrowFromNext(node, idx);
  else {
    if (idx != node->numKeys)
      merge(node, idx);
    else
      merge(node, idx - 1);
  }
}

B *deleteFromNode(B *node, int key) {
  int idx = findKey(node, key);
  if (idx < node->numKeys && node->keys[idx] == key) {
    if (node->isLeaf) {
      for (int i = idx + 1; i < node->numKeys; i++)
        node->keys[i - 1] = node->keys[i];
      node->numKeys--;
    } else {
      if (node->children[idx]->numKeys >= T) {
        B *cur = node->children[idx];
        while (!cur->isLeaf)
          cur = cur->children[cur->numKeys];
        node->keys[idx] = cur->keys[cur->numKeys - 1];
        node->children[idx] =
            deleteFromNode(node->children[idx], cur->keys[cur->numKeys - 1]);
      } else if (node->children[idx + 1]->numKeys >= T) {
        B *cur = node->children[idx + 1];
        while (!cur->isLeaf)
          cur = cur->children[0];
        node->keys[idx] = cur->keys[0];
        node->children[idx + 1] =
            deleteFromNode(node->children[idx + 1], cur->keys[0]);
      } else {
        merge(node, idx);
        node = deleteFromNode(node->children[idx], key);
      }
    }
  } else {
    if (node->isLeaf)
      return node;
    int flag = (idx == node->numKeys);
    if (node->children[idx]->numKeys < T)
      fill(node, idx);
    if (flag && idx > node->numKeys)
      node->children[idx - 1] = deleteFromNode(node->children[idx - 1], key);
    else
      node->children[idx] = deleteFromNode(node->children[idx], key);
  }
  if (node->numKeys == 0) {
    B *tmp = node;
    if (node->isLeaf)
      node = NULL;
    else
      node = node->children[0];
    free(tmp);
  }
  return node;
}

B *deleteNode(B *node, int key) {
  if (!node)
    return NULL;
  return deleteFromNode(node, key);
}

void inorder(B *node) {
  if (!node)
    return;
  int i;
  for (i = 0; i < node->numKeys; i++) {
    if (!node->isLeaf)
      inorder(node->children[i]);
    printf("%d ", node->keys[i]);
  }
  if (!node->isLeaf)
    inorder(node->children[i]);
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

void freeNode(B *node) {
  if (!node)
    return;
  if (!node->isLeaf)
    for (int i = 0; i <= node->numKeys; i++)
      if (node->children[i])
        freeNode(node->children[i]);
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
