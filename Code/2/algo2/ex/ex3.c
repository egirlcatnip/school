#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

node *create_node(int data) {
  node *new_node = (node *)malloc(sizeof(node));
  if (!new_node) {
    printf("Chyba alokace paměti!\n");
    return NULL;
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

int length(node *head) {
  int count = 0;
  while (head) {
    count++;
    head = head->next;
  }
  return count;
}

void print_node(node *head) {
  printf("[");
  while (head) {
    printf("%d", head->data);
    if (head->next)
      printf(", ");
    head = head->next;
  }
  printf("]\n");
}

node *add_start(node *head, node *insert_node) {
  insert_node->next = head;
  return insert_node;
}

node *add_end(node *head, node *insert_node) {
  if (!head)
    return insert_node;

  node *temp = head;
  while (temp->next)
    temp = temp->next;
  temp->next = insert_node;

  return head;
}

node *add_position(node *head, node *insert_node, int position) {
  if (position <= 0)
    return add_start(head, insert_node);

  node *temp = head;
  for (int i = 0; i < position - 1 && temp->next; i++) {
    temp = temp->next;
  }
  insert_node->next = temp->next;
  temp->next = insert_node;

  return head;
}

node *remove_start(node *head) {
  if (!head)
    return NULL;

  node *temp = head->next;
  free(head);

  return temp;
}

node *remove_end(node *head) {
  if (!head)
    return NULL;
  if (!head->next) {
    free(head);
    return NULL;
  }

  node *temp = head;
  while (temp->next->next)
    temp = temp->next;

  free(temp->next);
  temp->next = NULL;

  return head;
}

int search(node *head, node *search_node) {
  int index = 0;
  while (head) {
    if (head == search_node)
      return index;
    head = head->next;
    index++;
  }
  return -1;
}

node *remove_in(node *head, node *delete_node) {
  if (!head)
    return NULL;
  if (head == delete_node)
    return remove_start(head);

  node *temp = head;
  while (temp->next && temp->next != delete_node) {
    temp = temp->next;
  }
  if (temp->next) {
    node *to_delete = temp->next;
    temp->next = temp->next->next;
    free(to_delete);
  }
  return head;
}

typedef struct stack {
  node *top;
} stack;

stack *create_stack(void) {
  stack *s = (stack *)malloc(sizeof(stack));
  s->top = NULL;
  return s;
}

void push(stack *s, node *data) {
  data->next = s->top;
  s->top = data;
}

node *pop(stack *s) {
  if (!s->top)
    return NULL;

  node *temp = s->top;
  s->top = s->top->next;
  temp->next = NULL;

  return temp;
}

typedef struct queue {
  node *front;
  node *rear;
} queue;

void print_stack(stack *s) { print_node(s->top); }

void print_queue(queue *q) { print_node(q->front); }

queue *create_queue(void) {
  queue *q = (queue *)malloc(sizeof(queue));
  q->front = q->rear = NULL;
  return q;
}

void enqueue(queue *q, node *data) {
  if (!q->rear) {
    q->front = q->rear = data;
    return;
  }
  q->rear->next = data;
  q->rear = data;
}

node *dequeue(queue *q) {
  if (!q->front)
    return NULL;

  node *temp = q->front;
  q->front = q->front->next;

  if (!q->front)
    q->rear = NULL;

  temp->next = NULL;
  return temp;
}

int main(void) {
  printf("Created empty list\n");
  node *list = NULL;
  print_node(list);
  printf("List length: %d\n", length(list));

  printf("\n");

  list = add_end(list, create_node(10));
  printf("Added `10` to the end\n");
  list = add_end(list, create_node(20));
  printf("Added `20` to the end\n");
  list = add_start(list, create_node(5));
  printf("Added `5` to the start\n");

  print_node(list);
  printf("List length: %d\n", length(list));

  list = remove_end(list);
  printf("Removed `20` from the end\n");

  print_node(list);
  printf("List length: %d\n", length(list));

  printf("\n");

  printf("Created empty stack\n");
  stack *s = create_stack();
  print_stack(s);
  printf("Stack length: %d\n", length(s->top));

  push(s, create_node(1));
  printf("Pushed `1` to the stack\n");
  push(s, create_node(2));
  printf("Pushed `2` to the stack\n");
  push(s, create_node(3));
  printf("Pushed `3` to the stack\n");

  print_stack(s);
  printf("Stack length: %d\n", length(s->top));

  printf("Popped `%d` from stack\n", pop(s)->data);

  print_stack(s);
  printf("Stack length: %d\n", length(s->top));

  printf("\n");

  printf("Created empty queue\n");
  queue *q = create_queue();
  print_queue(q);
  printf("Queue length: %d\n", length(q->front));

  printf("Enqueueing `100` to the queue\n");
  enqueue(q, create_node(100));
  printf("Enqueueing `200` to the queue\n");
  enqueue(q, create_node(200));

  print_queue(q);
  printf("Queue length: %d\n", length(q->front));

  printf("Dequeued `%d` from queue\n", dequeue(q)->data);

  print_queue(q);
  printf("Queue length: %d\n", length(q->front));

  return 0;
}

// Konya

// Expected output:

/*
Created empty list
[]
List length: 0

Added `10` to the end
Added `20` to the end
Added `5` to the start
[5, 10, 20]
List length: 3
Removed `20` from the end
[5, 10]
List length: 2

Created empty stack
[]
Stack length: 0
Pushed `1` to the stack
Pushed `2` to the stack
Pushed `3` to the stack
[3, 2, 1]
Stack length: 3
Popped `3` from stack
[2, 1]
Stack length: 2

Created empty queue
[]
Queue length: 0
Enqueueing `100` to the queue
Enqueueing `200` to the queue
[100, 200]
Queue length: 2
Dequeued `100` from queue
[200]
Queue length: 1
*/
