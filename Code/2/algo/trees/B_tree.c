#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T 3
#define MAX_VALUE_COUNT (2 * T - 1)
#define MAX_CHILDREN_COUNT (2 * T)

typedef struct B {
  int values[MAX_VALUE_COUNT];
  int value_count; // 1-index based
  struct B *children[MAX_CHILDREN_COUNT];
  int child_count; // 1-index based

  bool is_leaf;
} B;

B *create_node(void) {
  B *node = malloc(sizeof(B));

  for (int i = 0; i < MAX_VALUE_COUNT; i++) {
    node->values[i] = 0;
  }
  node->value_count = 0;

  for (int i = 0; i < MAX_CHILDREN_COUNT; i++) {
    node->children[i] = NULL;
  }
  node->child_count = 0;

  node->is_leaf = true;

  return node;
}

void free_tree(B *node) {
  if (!node)
    return;

  for (int i = 0; i < node->child_count; i++) {
    free_tree(node->children[i]);
  }

  free(node);
}

void arr_insert(int a[], int value_count, int value) {
  for (int i = value_count - 1; i >= 0; i--) {
    if (a[i] > value) {
      a[i + 1] = a[i];
    }

    else {
      a[i + 1] = value;
      return;
    }
  }

  a[0] = value;
}

void split(B *node, int index) {
  B *temp = node->children[index];

  B *left = create_node();
  B *right = create_node();

  left->is_leaf = temp->is_leaf;
  right->is_leaf = temp->is_leaf;

  // insert into left 0..T-1
  for (int i = 0; i < T - 1; i++) {
    left->values[i] = temp->values[i];
  }
  left->value_count = T - 1;

  // insert into right T..2T-1
  for (int i = 0; i < T - 1; i++) {
    right->values[i] = temp->values[T + i];
  }
  right->value_count = temp->value_count - T;

  // move children if not leaf
  if (!temp->is_leaf) {
    // insert into left 0..T-1
    for (int i = 0; i < T; i++) {
      left->children[i] = temp->children[i];
    }
    left->child_count = T;

    // insert into right T..2T-1
    for (int i = 0; i < T; i++) {
      right->children[i] = temp->children[T + i];
    }
    right->child_count = temp->child_count - T;
  }

  // shift parent's children
  for (int i = node->child_count; i > index + 1; i--) {
    node->children[i] = node->children[i - 1];
  }

  node->children[index] = left;
  node->children[index + 1] = right;
  node->child_count++;

  // shift parent's values to insert up
  for (int i = node->value_count; i > index; i--) {
    node->values[i] = node->values[i - 1];
  }

  node->values[index] = temp->values[T - 1];
  node->value_count++;

  free(temp);
}

void insert_value(B *node, int value) {
  if (node->is_leaf) {
    arr_insert(node->values, node->value_count, value);
    node->value_count++;
    return;
  }

  else {
    // find child to insert into
    int i = 0;
    while (i < node->value_count && value >= node->values[i]) {
      i++;
    }

    // if child is not full, just insert
    if (node->children[i]->value_count != MAX_VALUE_COUNT) {
      insert_value(node->children[i], value);
    }

    else {
      split(node, i);
      insert_value(node, value);
    }
  }
}

B *insert(B *node, int value) {
  if (!node) {
    node = create_node();
    node->values[0] = value;
    node->value_count = 1;
    return node;
  }

  // if root is not full, just insert
  if (node->value_count != MAX_VALUE_COUNT) {
    insert_value(node, value);
    return node;
  }

  // if root is full, split it
  else {
    B *new_root = create_node();
    new_root->is_leaf = false;
    new_root->children[0] = node;
    new_root->child_count = 1;

    split(new_root, 0);
    insert_value(new_root, value);
    return new_root;
  }
}

void arr_delete(int a[], int count, int value) {
  int i = 0;
  while (i < count && a[i] != value)
    i++;

  while (i < count - 1) {
    a[i] = a[i + 1];

    i++;
  }
}

void delete_value(B *node, int value) {
  arr_delete(node->values, node->value_count, value);
  node->value_count--;
}

void borrow_left(B *parent, int index) {
  B *child = parent->children[index];
  B *left = parent->children[index - 1];

  for (int i = child->value_count; i > 0; i--)
    child->values[i] = child->values[i - 1];
  child->values[0] = parent->values[index - 1];
  child->value_count++;

  if (!child->is_leaf) {
    for (int i = child->child_count; i > 0; i--)
      child->children[i] = child->children[i - 1];

    left->child_count--;

    child->children[0] = left->children[left->child_count];
    child->child_count++;
  }

  left->value_count--;
  parent->values[index - 1] = left->values[left->value_count];
}

void borrow_right(B *parent, int index) {
  B *child = parent->children[index];
  B *right = parent->children[index + 1];

  child->values[child->value_count] = parent->values[index];
  parent->values[index] = right->values[0];
  child->value_count++;

  for (int i = 0; i < right->value_count - 1; i++)
    right->values[i] = right->values[i + 1];
  right->value_count--;

  if (!right->is_leaf) {
    child->children[child->child_count] = right->children[0];
    child->child_count++;
    right->child_count--;

    for (int i = 0; i < right->child_count; i++) {
      right->children[i] = right->children[i + 1];
    }
  }
}

void merge(B *parent, int index) {
  B *left = parent->children[index];
  B *right = parent->children[index + 1];

  left->values[left->value_count] = parent->values[index];
  left->value_count++;

  for (int i = 0; i < right->value_count; i++) {
    left->values[left->value_count] = right->values[i];
    left->value_count++;
  }

  if (!left->is_leaf) {
    for (int i = 0; i < right->child_count; i++) {
      left->children[left->child_count] = right->children[i];
      left->child_count++;
    }
  }

  for (int i = index; i < parent->value_count - 1; i++) {
    parent->values[i] = parent->values[i + 1];
  }

  for (int i = index + 1; i < parent->child_count - 1; i++) {
    parent->children[i] = parent->children[i + 1];
  }

  parent->value_count--;
  parent->child_count--;

  free(right);
}

int get_predecessor(B *node, int index) {
  B *current = node->children[index];
  while (!current->is_leaf)
    current = current->children[current->child_count - 1];

  return current->values[current->value_count - 1];
}

int get_successor(B *node, int index) {
  B *current = node->children[index + 1];
  while (!current->is_leaf)
    current = current->children[0];

  return current->values[0];
}

B *delete_node(B *node, int value);

void handle_merging(B *node, int value, int index) {
  if (node->values[index] == value) {
    B *left = node->children[index];
    B *right = node->children[index + 1];

    if (left->value_count >= T) {
      int pred = get_predecessor(node, index);
      node->values[index] = pred;
      node->children[index] = delete_node(left, pred);
      return;
    }

    if (right->value_count >= T) {
      int succ = get_successor(node, index);
      node->values[index] = succ;
      node->children[index + 1] = delete_node(right, succ);
      return;
    }

    merge(node, index);
    node->children[index] = delete_node(node->children[index], value);
    return;
  }

  B *child = node->children[index];
  if (child->value_count == T - 1) {
    if (index > 0 && node->children[index - 1]->value_count >= T)
      borrow_left(node, index);

    else if (index + 1 < node->child_count &&
             node->children[index + 1]->value_count >= T)
      borrow_right(node, index);

    else {
      if (index + 1 < node->child_count) {
        merge(node, index);
        child = node->children[index];
      }

      else {
        merge(node, index - 1);
        child = node->children[index - 1];
      }
    }
  }
  node->children[index] = delete_node(child, value);
}
bool search(B *node, int value);

B *delete_node(B *node, int value) {
  if (!node || !search(node, value))
    return node;

  int index = 0;
  while (index < node->value_count && value > node->values[index])
    index++;

  if (index < node->value_count) {
    if (node->is_leaf)
      delete_value(node, value);
    else
      handle_merging(node, value, index);
  }

  else {
    if (node->is_leaf)
      return node;

    handle_merging(node, value, index);
  }

  if (node->value_count == 0 && !node->is_leaf) {
    B *temp = node->children[0];
    free(node);
    return temp;
  }

  return node;
}

void inorder(B *node) {
  if (!node)
    return;

  for (int i = 0; i < node->value_count; i++) {
    if (!node->is_leaf) {
      inorder(node->children[i]);
    }
    printf("%d ", node->values[i]);
  }

  if (!node->is_leaf) {
    inorder(node->children[node->child_count - 1]);
  }
}

bool search(B *node, int value) {
  if (!node)
    return false;

  int i = 0;
  while (i < node->value_count && value > node->values[i])
    i++;

  if (i < node->value_count && value == node->values[i])
    return true;

  if (node->is_leaf)
    return false;

  return search(node->children[i], value);
}

void print_node(B *node) {
  if (!node)
    return;

  printf("[ ");
  for (int i = 0; i < node->value_count; i++) {
    if (!node->is_leaf)
      printf("(c%d) ", i);
    printf("%d ", node->values[i]);
  }

  if (!node->is_leaf)
    printf("(c%d) ", node->child_count - 1);

  printf("]\n");
}

void print_children(B *node, int depth) {
  if (!node)
    return;

  for (int i = 0; i < node->child_count; i++) {
    for (int j = 0; j < depth; j++) {
      printf("  ");
    }
    printf("(c%d): ", i);
    print_node(node->children[i]);
    print_children(node->children[i], depth + 1);
  }
}

void print_whole(B *node) {
  if (!node) {
    return;
  }

  print_node(node);
  print_children(node, 1);
}

int main(void) {
  B *root = NULL;
  int number = 0;

  printf("INSERTION\n");

  number = 10;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 20;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 5;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 6;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 12;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 30;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 7;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 17;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 50;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  number = 66;
  printf("Adding %d\n", number);
  root = insert(root, number);
  print_whole(root);
  printf("\n");

  printf("INORDER\n");
  printf("Inorder traversal:\n");
  inorder(root);
  printf("\n");

  printf("\n");

  printf("SEARCH\n");
  number = 7;
  printf("Searching for %d\n", number);
  bool searched = search(root, number);

  if (searched) {
    printf("Found\n");
  }

  else {
    printf("Not found\n");
  }

  printf("\n");

  printf("DELETION\n");

  number = 17;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);
  printf("\n");

  number = 7;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);
  printf("\n");

  number = 66;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);
  printf("\n");

  number = 50;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);
  printf("\n");

  number = 12;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);
  printf("\n");

  number = 10;
  printf("Deleting %d\n", number);
  root = delete_node(root, number);
  print_whole(root);

  free_tree(root);
  return 0;
}

// Konya

/*
INSERTION
Adding 10
[ 10 ]

Adding 20
[ 10 20 ]

Adding 5
[ 5 10 20 ]

Adding 6
[ 5 6 10 20 ]

Adding 12
[ 5 6 10 12 20 ]

Adding 30
[ (c0) 10 (c1) ]
  (c0): [ 5 6 ]
  (c1): [ 12 20 30 ]

Adding 7
[ (c0) 10 (c1) ]
  (c0): [ 5 6 7 ]
  (c1): [ 12 20 30 ]

Adding 17
[ (c0) 10 (c1) ]
  (c0): [ 5 6 7 ]
  (c1): [ 12 17 20 30 ]

Adding 50
[ (c0) 10 (c1) ]
  (c0): [ 5 6 7 ]
  (c1): [ 12 17 20 30 50 ]

Adding 66
[ (c0) 10 (c1) 20 (c2) ]
  (c0): [ 5 6 7 ]
  (c1): [ 12 17 ]
  (c2): [ 30 50 66 ]

INORDER
Inorder traversal:
5 6 7 10 12 17 20 30 50 66

SEARCH
Searching for 7
Found

DELETION
Deleting 17
[ (c0) 7 (c1) 20 (c2) ]
  (c0): [ 5 6 ]
  (c1): [ 10 12 ]
  (c2): [ 30 50 66 ]

Deleting 7
[ (c0) 20 (c1) ]
  (c0): [ 5 6 10 12 ]
  (c1): [ 30 50 66 ]

Deleting 66
[ (c0) 20 (c1) ]
  (c0): [ 5 6 10 12 ]
  (c1): [ 30 50 ]

Deleting 50
[ (c0) 12 (c1) ]
  (c0): [ 5 6 10 ]
  (c1): [ 20 30 ]

Deleting 12
[ (c0) 10 (c1) ]
  (c0): [ 5 6 ]
  (c1): [ 20 30 ]

Deleting 10
[ 5 6 20 30 ]
*/
