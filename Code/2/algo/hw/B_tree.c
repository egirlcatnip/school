#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T 3
#define MAX_VALUE_COUNT (2 * T - 1)
#define MAX_CHILD_COUNT (2 * T)

typedef struct B {
  int values[MAX_VALUE_COUNT + 1]; // +1 for the value at split
  int value_count;

  struct B *children[MAX_CHILD_COUNT];
  int children_count;
  bool is_leaf;
} B;

B *createNode(void) {
  B *Node = malloc(sizeof(B));

  Node->value_count = 0;
  Node->children_count = 0;
  Node->is_leaf = true;

  return Node;
}

void freeNode(B *node) {
  if (!node)
    return;
  for (int i = 0; i < node->children_count; i++)
    freeNode(node->children[i]);
  free(node);
}

void array_insert(int *array, int length, int value) {
  for (int i = 0; i < length; i++) {
    if (array[i] == 0 || value < array[i]) {
      for (int j = length - 1; j > i; j--) {
        array[j] = array[j - 1];
      }
      array[i] = value;
      break;
    }
  }
}

B *insertNode(B *node, int value);

B *nodeToInsertInto(B *node, int value) {
  if (!node->is_leaf) {
    // Find the child to insert into
    int i = 0;
    while (i < node->value_count && value > node->values[i])
      i++;
    return node->children[i];
  }
  return node;
}

B *insertValue(B *node, int value) {

  B *child_node = nodeToInsertInto(node, value);

  array_insert(child_node->values, MAX_VALUE_COUNT + 1, value);

  child_node->value_count++;
  return node;
}

B *split(B *node, int value) {
  B *child_node = nodeToInsertInto(node, value);

  printf("split\n");
  B *left_node = createNode();
  B *right_node = createNode();

  int mid_index = T - 1;

  if (!child_node->is_leaf) {
    B *new_node = node;

    // insert 2 values to left
    for (int i = 0; i < T - 1; i++) {
      left_node = insertValue(left_node, node->values[i]);
    }

    // insert 3 values to right
    for (int i = T + 1; i < MAX_VALUE_COUNT; i++) {
      right_node = insertValue(right_node, node->values[i]);
    }

    new_node = insertValue(new_node, node->values[mid_index]);
    new_node->is_leaf = false;

    // Shift old children to the right to make space for the new child
    for (int i = new_node->children_count; i > mid_index; i--) {
      new_node->children[i + 1] = new_node->children[i];
    }

    int index_left = node->children_count;
    int index_right = node->children_count + 1;

    //

    new_node->children[index_left] = left_node;
    new_node->children[index_right] = right_node;

    return new_node;
  }

  else if (!node->is_leaf && node->children_count > 0) {
    B *new_node = node;

    // insert 2 values to left
    for (int i = 0; i < T - 1; i++) {
      left_node = insertValue(left_node, node->values[i]);
    }

    // insert 3 values to right
    for (int i = T + 1; i < MAX_VALUE_COUNT; i++) {
      right_node = insertValue(right_node, node->values[i]);
    }

    new_node = insertValue(new_node, node->values[mid_index]);

    new_node->is_leaf = false;

    int index_left = new_node->children_count;
    int index_right = new_node->children_count + 1;

    new_node->children[index_left] = left_node;
    new_node->children[index_right] = right_node;

    return new_node;
  }

  else { // No parent, 2 new nodes
    B *new_node = createNode();

    // insert 2 values to left
    for (int i = 0; i < mid_index; i++) {
      left_node = insertValue(left_node, node->values[i]);
    }

    // insert 3 values to right
    for (int i = mid_index + 1; i < MAX_VALUE_COUNT + 1; i++) {
      right_node = insertValue(right_node, node->values[i]);
    }

    new_node = insertValue(new_node, node->values[mid_index]);

    if (node->children_count == 0) {
      new_node->is_leaf = false;

      int index_left = new_node->children_count;
      int index_right = new_node->children_count + 1;

      new_node->children[index_left] = left_node;
      new_node->children[index_right] = right_node;
      new_node->children_count = 2;

    } else {
      new_node->children_count = node->children_count + 1;

      int index_left = new_node->children_count - 1;
      int index_right = new_node->children_count;

      new_node->children[index_left] = left_node;
      new_node->children[index_right] = right_node;
    }

    return new_node;
  }
}

B *insertNode(B *node, int value) {
  printf("+%d\n", value);

  // New root
  if (!node) {
    node = createNode();
    node->values[0] = value;
    node->value_count = 1;
    return node;
  }

  if (node->is_leaf) {
    // Full node
    if (node->value_count == MAX_VALUE_COUNT) {
      node = insertValue(node, value);
      node = split(node, value);
      return node;
    }

    // Non-full root
    node = insertValue(node, value);
    return node;

  } else {
    // Handle pushing up to parent
    B *child_node = nodeToInsertInto(node, value);
    if (child_node->value_count == MAX_VALUE_COUNT) {
      child_node = insertValue(child_node, value);
      node = split(child_node, value);

      return node;

    } else {
      // Non-full child
      child_node = insertValue(child_node, value);
      return node;
    }
  }
}

B *search(B *node, int value) {
  int i = 0;
  while (i < node->value_count && value > node->values[i])
    i++;
  if (i < node->value_count && node->values[i] == value)
    return node;
  if (node->is_leaf)
    return NULL;
  return search(node->children[i], value);
}

void inorder(B *node) {
  if (!node)
    return;
  for (int i = 0; i < node->value_count; i++) {
    if (!node->is_leaf)
      inorder(node->children[i]);
    printf("%d ", node->values[i]);
  }
  if (!node->is_leaf)
    inorder(node->children[node->value_count]);
}

void printNode(B *node) {
  printf("[ ");
  for (int i = 0; i < node->value_count; i++) {
    if (node->children[i])
      printf("(c%d) ", i);
    if (node->values[i])
      printf("%d ", node->values[i]);
  }
  if (node->children[node->value_count])
    printf("(c%d) ", node->value_count);
  printf("]\n");
}

void printChildren(B *node) {
  for (int i = 0; i < node->children_count; i++) {
    printf("(c%d): ", i);
    printNode(node->children[i]);
  }
}

int getHeight(B *node) {
  if (!node)
    return 0;
  if (node->is_leaf)
    return 1;
  return 1 + getHeight(node->children[0]);
}

int main(void) {
  B *root = NULL;

  root = insertNode(root, 10);
  root = insertNode(root, 20);
  root = insertNode(root, 5);
  root = insertNode(root, 6);
  root = insertNode(root, 12);
  root = insertNode(root, 30);
  root = insertNode(root, 7);
  root = insertNode(root, 17);
  root = insertNode(root, 50);

  printNode(root);
  printf("\n");
  printf("Children:\n");
  printChildren(root);
  printf("\n");

  root = insertNode(root, 66);

  printNode(root);
  printf("\n");
  printf("Children:\n");
  printChildren(root);
  printf("\n");

  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  printf("\n");

  printf("Tree height: %d\n", getHeight(root));

  printf("\n");

  printf("Root keys:\n");
  printNode(root);

  printf("\n");

  printf("Root children:\n");
  printChildren(root);

  freeNode(root);
  return 0;
}
