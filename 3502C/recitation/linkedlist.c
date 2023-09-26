#include <stdlib.h>
#include <string.h>

typedef struct node {
  char letter;
  struct node* next;
} node;

int length(node* head) {
  int len = 0;

  if (head->next != NULL) {
    len += length(head->next);
  }
  len++;

  return len;
};

char* toCString(node* head) {
  int len = length(head);
  char* letter = head->letter;

  if (head->next != NULL) {
    letter = strcat(letter, toCString(head->next));
  }

  return letter;
};

typedef struct node2 {
  int data;
  struct node2* next;
} node2;

void markEven(node2* head){

};
