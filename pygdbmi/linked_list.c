#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
};

/**
 * Does our debugger algorithm for converting a linked list to JSON data
 * representation generalise to a tree data structure?
 *
 */
struct tree_node {
  int data;
  struct tree_node *left;
  struct tree_node *right;
  struct tree_node *center;
};

struct list {
  struct node *head;
};

struct node *create_new_node(int data) {
  struct node *new = malloc(sizeof(struct node));
  new->data = data;
  new->next = NULL;
  return new;
}

void append(int value, struct list *list) {
  struct node *new_tail = create_new_node(value);
  if (list->head == NULL) {
    list->head = new_tail;
    return;
  }

  struct node *curr = list->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = new_tail;
};

void print_list(struct list *list) {
  struct node *curr = list->head;
  while (curr != NULL) {
    printf("%d -> ", curr->data);
    curr = curr->next;
  }
  printf("X\n");
}

int main(int argc, char *argv[]) {
  struct list *list = malloc(sizeof(struct list));
  list->head = NULL; // 0x432ade27 -> 0x737ade27 -> 0x9564aed -> 0x00000000
  append(5, list);
  append(10, list);
  print_list(list);
}
