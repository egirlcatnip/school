#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
  int numKeys;
  int keys[2 * T - 1];
  struct BTreeNode *children[2 * T];
  bool isLeaf;
} BTreeNode;

BTreeNode *createNode(bool isLeaf) {
  BTreeNode *node = malloc(sizeof(BTreeNode));
  node->isLeaf = isLeaf;
  node->numKeys = 0;
  for (int i = 0; i < 2 * T; i++)
    node->children[i] = NULL;
  return node;
}

BTreeNode *searchKey(BTreeNode *root, int key) {
  if (!root)
    return NULL;
  int i = 0;
  while (i < root->numKeys && key > root->keys[i])
    i++;
  if (i < root->numKeys && root->keys[i] == key)
    return root;
  if (root->isLeaf)
    return NULL;
  return searchKey(root->children[i], key);
}

void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
  BTreeNode *newChild = createNode(child->isLeaf);
  newChild->numKeys = T - 1;
  for (int j = 0; j < T - 1; j++)
    newChild->keys[j] = child->keys[j + T];
  if (!child->isLeaf)
    for (int j = 0; j < T; j++)
      newChild->children[j] = child->children[j + T];
  child->numKeys = T - 1;
  for (int j = parent->numKeys; j >= index + 1; j--)
    parent->children[j + 1] = parent->children[j];
  parent->children[index + 1] = newChild;
  for (int j = parent->numKeys - 1; j >= index; j--)
    parent->keys[j + 1] = parent->keys[j];
  parent->keys[index] = child->keys[T - 1];
  parent->numKeys++;
}

void insertNonFull(BTreeNode *node, int key) {
  int i = node->numKeys - 1;
  if (node->isLeaf) {
    while (i >= 0 && node->keys[i] > key) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = key;
    node->numKeys++;
  } else {
    while (i >= 0 && node->keys[i] > key)
      i--;
    i++;
    if (node->children[i]->numKeys == 2 * T - 1) {
      splitChild(node, i, node->children[i]);
      if (node->keys[i] < key)
        i++;
    }
    insertNonFull(node->children[i], key);
  }
}

BTreeNode *insert(BTreeNode *root, int key) {
  if (!root) {
    root = createNode(true);
    root->keys[0] = key;
    root->numKeys = 1;
    return root;
  }
  if (root->numKeys == 2 * T - 1) {
    BTreeNode *newRoot = createNode(false);
    newRoot->children[0] = root;
    splitChild(newRoot, 0, root);
    int i = 0;
    if (newRoot->keys[0] < key)
      i++;
    insertNonFull(newRoot->children[i], key);
    return newRoot;
  } else {
    insertNonFull(root, key);
    return root;
  }
}

int getPredecessor(BTreeNode *node, int index) {
  BTreeNode *current = node->children[index];
  while (!current->isLeaf)
    current = current->children[current->numKeys];
  return current->keys[current->numKeys - 1];
}

int getSuccessor(BTreeNode *node, int index) {
  BTreeNode *current = node->children[index + 1];
  while (!current->isLeaf)
    current = current->children[0];
  return current->keys[0];
}

void merge(BTreeNode *node, int index) {
  BTreeNode *child = node->children[index];
  BTreeNode *sibling = node->children[index + 1];
  child->keys[T - 1] = node->keys[index];
  for (int i = 0; i < sibling->numKeys; i++)
    child->keys[i + T] = sibling->keys[i];
  if (!child->isLeaf)
    for (int i = 0; i <= sibling->numKeys; i++)
      child->children[i + T] = sibling->children[i];
  child->numKeys += sibling->numKeys + 1;
  for (int i = index + 1; i < node->numKeys; i++) {
    node->keys[i - 1] = node->keys[i];
    node->children[i] = node->children[i + 1];
  }
  node->numKeys--;
  free(sibling);
}

void fill(BTreeNode *node, int index) {
  if (index != 0 && node->children[index - 1]->numKeys >= T) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index - 1];
    for (int i = child->numKeys - 1; i >= 0; i--)
      child->keys[i + 1] = child->keys[i];
    if (!child->isLeaf)
      for (int i = child->numKeys; i >= 0; i--)
        child->children[i + 1] = child->children[i];
    child->keys[0] = node->keys[index - 1];
    if (!child->isLeaf)
      child->children[0] = sibling->children[sibling->numKeys];
    node->keys[index - 1] = sibling->keys[sibling->numKeys - 1];
    child->numKeys++;
    sibling->numKeys--;
  } else if (index != node->numKeys &&
             node->children[index + 1]->numKeys >= T) {
    BTreeNode *child = node->children[index];
    BTreeNode *sibling = node->children[index + 1];
    child->keys[child->numKeys] = node->keys[index];
    if (!child->isLeaf)
      child->children[child->numKeys + 1] = sibling->children[0];
    node->keys[index] = sibling->keys[0];
    for (int i = 1; i < sibling->numKeys; i++)
      sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->isLeaf)
      for (int i = 1; i <= sibling->numKeys; i++)
        sibling->children[i - 1] = sibling->children[i];
    child->numKeys++;
    sibling->numKeys--;
  } else {
    if (index != node->numKeys)
      merge(node, index);
    else
      merge(node, index - 1);
  }
}

void removeFromLeaf(BTreeNode *node, int index) {
  for (int i = index + 1; i < node->numKeys; i++)
    node->keys[i - 1] = node->keys[i];
  node->numKeys--;
}

void removeKey(BTreeNode *node, int key);

void removeFromNonLeaf(BTreeNode *node, int index) {
  int keyVal = node->keys[index];
  if (node->children[index]->numKeys >= T) {
    int pred = getPredecessor(node, index);
    node->keys[index] = pred;
    removeKey(node->children[index], pred);
  } else if (node->children[index + 1]->numKeys >= T) {
    int succ = getSuccessor(node, index);
    node->keys[index] = succ;
    removeKey(node->children[index + 1], succ);
  } else {
    merge(node, index);
    removeKey(node->children[index], keyVal);
  }
}

void removeKey(BTreeNode *node, int key) {
  int index = 0;
  while (index < node->numKeys && node->keys[index] < key)
    index++;
  if (index < node->numKeys && node->keys[index] == key) {
    if (node->isLeaf)
      removeFromLeaf(node, index);
    else
      removeFromNonLeaf(node, index);
  } else {
    if (node->isLeaf)
      return;
    bool flag = (index == node->numKeys);
    if (node->children[index]->numKeys < T)
      fill(node, index);
    if (flag && index > node->numKeys)
      removeKey(node->children[index - 1], key);
    else
      removeKey(node->children[index], key);
  }
}

BTreeNode *removeKeyFromTree(BTreeNode *root, int key) {
  if (!root)
    return root;
  removeKey(root, key);
  if (root->numKeys == 0) {
    BTreeNode *temp = root;
    if (root->isLeaf) {
      free(root);
      return NULL;
    } else {
      root = root->children[0];
      free(temp);
    }
  }
  return root;
}

void traverse(BTreeNode *root) {
  if (root != NULL) {
    int i;
    for (i = 0; i < root->numKeys; i++) {
      if (!root->isLeaf)
        traverse(root->children[i]);
      printf("%d ", root->keys[i]);
    }
    if (!root->isLeaf)
      traverse(root->children[i]);
  }
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

  printf("Traversal of the constructed B-Tree:\n");
  traverse(root);
  printf("\n");

  printf("Removing 6...\n");
  root = removeKeyFromTree(root, 6);
  printf("Traversal after removing 6:\n");
  traverse(root);
  printf("\n");

  printf("Removing 13...\n");
  root = removeKeyFromTree(root, 13);
  printf("Traversal after removing 13:\n");
  traverse(root);
  printf("\n");

  return 0;
}
