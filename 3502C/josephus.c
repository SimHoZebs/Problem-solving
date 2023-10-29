#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <

/*
gcc -g -O2 -std=c11 -o a josephus.c -lm && ./a
type ./input.md | ./a.exe > ./output.md
*/

typedef struct node {
  int data;
  struct node* next;
} node;
node* makeNode(int val) {
  node* newNode = {val};
  return newNode;
};

int main() { return 0; }

struct node* makeCircular(int n) {
  if (n == 1) {
    node* tmp = makeNode(1);
    tmp->next = tmp;
    return tmp;
  }

  node* front = makeNode(1);
  node* back = front;

  for (int i = 2; i <= n; i++) {
    node* newNode = makeNode(i);
    back->next = newNode;
    back = newNode;
  }

  back->next = front;

  return front;
}

void print(node* front) {
  if (front == NULL) {
  }
}