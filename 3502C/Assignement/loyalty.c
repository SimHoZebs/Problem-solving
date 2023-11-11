#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_MAX 13
#define NAME_MAX 19

/*
gcc -g -O2 -std=c11 -o a loyalty.c -lm
gcc -g -O2 -std=c11 -o a loyalty.c -lm && ./a
stdbuf -i0 -o0 -e0 ./a < ./input.in > ./test.out
diff -y output.out test.out | tee diff.txt
*/

typedef struct Customer {
  char name[NAME_MAX + 1];
  int points;
} Customer;

typedef struct Node {
  Customer* data;
  struct Node* left;
  struct Node* right;
  int size;
} Node;

// returns the child node to traverse to
Node* nextNode(Node* node, char name[]) {
  int cmp = strcmp(node->data->name, name);

  if (cmp > 0) {
    return (node->left);
  } else if (cmp < 0) {
    return node->right;
  }
  // when current node is the target; should never happen.
  else {
    printf("ERROR: node is the target.\n");
    return NULL;
  }
}

Node* getNode(Node* node, char name[]) {
  if (!node || !node->data) return NULL;

  Customer* customer = node->data;

  if (strcmp(customer->name, name) == 0) {
    return node;
  } else {
    return getNode(nextNode(node, name), name);
  }
}

void search(Node* node, char* name, int depth) {
  if (!node || !node->data) {
    printf("%s not found", name);
    return;
  }

  Customer* customer = node->data;

  if (strcmp(customer->name, name) != 0) {
    search(nextNode(node, name), name, depth + 1);
  } else {
    printf("%s %d %d", name, customer->points, depth);
  }
};

void test(Node* node) {
  printf("---TEST---\n");
  printf("node pointer: %p\n", node);
  if (!node) return;
  printf("node data pointer: %p\n", node->data);
  if (node->data) printf("node data name: %s\n", node->data->name);
  printf("node left pointer: %p\n", node->left);
  if (node->left) printf("node left data name: %s\n", node->left->data->name);
  printf("node right pointer: %p\n", node->right);
  if (node->right)
    printf("node right data name: %s\n", node->right->data->name);
  printf("---END---\n");
}

void add(Node* node, char name[], int points, Node* customerExists) {
  // NULL node - should never happen, but just in case.
  if (!node) {
    printf("this node is NULL\n");
    return;
  }

  Customer* customer = node->data;

  // customer doesn't exist in tree; create new node
  if (customer == NULL) {
    customer = calloc(1, sizeof(Customer));
    strcpy(customer->name, name);
    customer->points = points;

    node->data = customer;
    node->size = 1;
    printf("%s %d", customer->name, customer->points);
  }
  // customer found, so add points
  else if (strcmp(customer->name, name) == 0) {
    customer->points += points;
    printf("%s %d", customer->name, customer->points);
  }
  // customer belongs under this node
  else {
    if (!customerExists) node->size++;

    if (strcmp(customer->name, name) > 0) {
      if (!node->left) node->left = calloc(1, sizeof(Node));

      add(node->left, name, points, customerExists);
    } else {
      if (!node->right) node->right = calloc(1, sizeof(Node));

      add(node->right, name, points, customerExists);
    }
  }
};

void sub(Node* node, char name[], int points) {
  Customer* customer = node->data;

  if (strcmp(customer->name, name) == 0) {
    customer->points -= points;
    if (customer->points < 0) customer->points = 0;
    printf("%s %d", customer->name, customer->points);
  } else {
    sub(nextNode(node, name), name, points);
  }
};

Node* getMaxNode(Node* node, char currMaxName[]) {
  // NULL node - should never happen, but just in case.
  if (!node) {
    printf("this node is NULL\n");
    return NULL;
  }

  Customer* customer = node->data;

  // if empty tree
  if (customer == NULL) return node;

  if (customer->name > currMaxName) currMaxName = customer->name;

  if (node->right) {
    getMaxNode(node->right, currMaxName);
  } else if (node->left) {
    getMaxNode(node->left, currMaxName);
  } else {
    return node;
  }
}

Node* getMinNode(Node* node, char currMinName[]) {
  // node should be NULL, but just in case.
  if (!node) {
    printf("this node is NULL\n");
    return NULL;
  }

  Customer* customer = node->data;

  // if empty tree
  if (customer == NULL) return node;

  if (customer->name < currMinName) currMinName = customer->name;

  if (node->left) {
    getMinNode(node->left, currMinName);
  } else if (node->right) {
    getMinNode(node->right, currMinName);
  } else {
    return node;
  }
}

// recrusively replaces node data and deletes empty leaf node.
// as del() only runs when customer exists, node is never NULL.
Node* del(Node* node, char name[]) {
  // test(node);
  Customer* customer = node->data;

  if (strcmp(customer->name, name) == 0) {
    Node* maxNode = getMaxNode(node, name);

    // try to use left max value as per program requirement
    if (node->left) {
      Node* maxNode = getMaxNode(node->left, name);
      node->data = maxNode->data;

      // now that the data is replaced, delete that node.
      node->left = del(node->left, maxNode->data->name);
      return node->left;
    }
    // if left node doesn't exist, use right min value
    else if (node->right) {
      Node* minNode = getMinNode(node->right, name);
      node->data = minNode->data;

      // now that the data is replaced, delete that node.
      node->right = del(node->right, minNode->data->name);
      return node->right;
    }
    // if leaf node, delete the node.
    else {
      free(node);
      return NULL;
    }
  } else {
    printf("reducing node size customer %s\n", node->data->name);
    node->size--;
    if (strcmp(customer->name, name) > 0)
      node->left = del(node->left, name);
    else
      node->right = del(node->right, name);
  }

  return node;
};

int countSmaller(Node* node, char* name, int count) {
  if (!node) {
    return count;
  }
  Customer* customer = node->data;

  if (strcmp(customer->name, name) > 0) {
    return countSmaller(node->left, name, count);
  } else if (strcmp(customer->name, name) < 0) {
    if (node->left) count += node->left->size;
    return countSmaller(node->right, name, count + 1);
  } else {
    if (node->left) count += node->left->size;
    return count;
  }
};

int main() {
  int count;
  scanf("%d", &count);

  Node* root = calloc(1, sizeof(Node));

  for (int i = 0; i < count; i++) {
    char* command = calloc(1, (1 + COMMAND_MAX) * sizeof(char));
    char* name = calloc(1, (1 + NAME_MAX) * sizeof(char));
    int points = 0;
    scanf("%s %s", command, name);

    // printf("command: %s, name: %s\n", command, name);
    // since all commands start with a unique char (except search and sub),
    // we can check the first char instead of the whole string
    switch (command[0]) {
      // search or sub
      case 's':
        // search
        if (strcmp(command, "search") == 0) {
          search(root, name, 0);
        }
        // sub
        else {
          scanf("%d", &points);
          if (!getNode(root, name)) {
            printf("%s not found", name);
          } else {
            sub(root, name, points);
          }
        }
        break;

      // del
      case 'd':
        Node* node = getNode(root, name);

        // run del only if customer exists
        if (node) {
          Customer* customer = node->data;

          del(root, name);

          // free target customer; this can't be done inside del as the
          // recursive call would free customer replacing the target
          free(customer);
          printf("%s deleted", name);
        }
        // otherwise skip
        else {
          printf("%s not found", name);
        }
        break;

      // count_smaller
      case 'c':
        printf("%d", countSmaller(root, name, 0));
        break;

      // add
      case 'a':
        scanf("%d", &points);
        add(root, name, points, getNode(root, name));
        break;
      case 't':
        test(getNode(root, name));
    }

    printf("\n");
  }

  return 0;
}