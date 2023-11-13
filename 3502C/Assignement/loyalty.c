/*
Ho Sim
loyalty.c
12th NOV 2023
*/

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

// debugging purposes
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

// compares a node to a value; here, the value are names.
int compareBST(Node* node, char name2[]) {
  return strcmp(node->data->name, name2);
}

// compare two customers. 1 when first is larger, 0 if equal, -1 otherwise.
int compareMerge(Customer* c1, Customer* c2) {
  // c1 has more points
  if (c1->points > c2->points) return 1;
  // c2 has more points
  else if (c1->points < c2->points)
    return -1;
  // c1 and c2 have same points
  else
    return 0;
}

// returns the child node to traverse to
Node* nextNode(Node* node, char name[]) {
  int cmp = compareBST(node, name);

  if (cmp > 0)
    return (node->left);
  else if (cmp < 0)
    return node->right;
}

// recursively search for node
void searchRecursive(Node* node, char name[], int depth) {
  if (!node || !node->data)
    printf("%s not found", name);
  else if (compareBST(node, name) != 0)
    searchRecursive(nextNode(node, name), name, depth + 1);
  else
    printf("%s %d %d", name, node->data->points, depth);
};

// search with default depth of 0
void search(Node* node, char name[]) { searchRecursive(node, name, 0); }

// like search but without depth and print
Node* getNode(Node* node, char name[]) {
  if (!node || !node->data) return NULL;

  if (compareBST(node, name) != 0) {
    getNode(nextNode(node, name), name);
  } else {
    return node;
  }
}

Customer* createCustomer(char name[], int points) {
  Customer* customer = calloc(1, sizeof(Customer));
  strcpy(customer->name, name);
  customer->points = points;
  return customer;
}

// create node WITHOUT customer;
Node* createNode(char name[], int points) {
  // allocate with calloc to set default values to 0/NULL
  Node* tmp = calloc(1, sizeof(Node));
  tmp->data = createCustomer(name, points);
  tmp->size = 1;
  return tmp;
}

void insert(Node* node, char name[], int points) {
  // NULL node - should never happen, but just in case.
  if (!node) {
    printf("this node is NULL\n");
    return;
  }

  Customer* customer = node->data;

  // customer doesn't exist in tree; create new node
  if (customer == NULL) {
    customer = createCustomer(name, points);

    node->data = customer;
    node->size = 1;
    printf("%s %d", customer->name, customer->points);
  }
  // customer found
  else if (strcmp(customer->name, name) == 0) {
    printf("%s %d", customer->name, customer->points);
  }
  // customer belongs under this node
  else {
    node->size++;

    if (strcmp(customer->name, name) > 0) {
      // if empty node
      if (!node->left) node->left = createNode(name, points);
      insert(node->left, name, points);
    } else {
      // if empty node
      if (!node->right) node->right = createNode(name, points);
      insert(node->right, name, points);
    }
  }
};

void sub(Node* node, char name[], int points) {
  Customer* customer = node->data;
  int cmp = compareBST(node, name);

  if (cmp == 0) {
    // subtract points
    customer->points -= points;

    // if points go under 0, set it to 0
    if (customer->points < 0) customer->points = 0;

    printf("%s %d", customer->name, customer->points);
  } else {
    sub(nextNode(node, name), name, points);
  }
};

Node* getMaxNode(Node* node) {
  // NULL node - should never happen, but just in case.
  if (!node) {
    printf("this node is NULL\n");
    return NULL;
  }

  if (node->right == NULL)
    return node;
  else
    return getMaxNode(node->right);
}

// recrusively replaces node data and deletes empty leaf node.
// as del() only runs when customer exists, node is never NULL.
Node* del(Node* node, char name[]) {
  node->size--;

  // if target node is found
  if (compareBST(node, name) == 0) {
    // if only left node
    if (node->left && !node->right) {
      // then use it to fill the gap
      Node* replacer = node->left;
      free(node);
      return replacer;
    }
    // if only right node
    else if (node->right && !node->left) {
      // then use it to fill the gap
      Node* replacer = node->right;

      free(node);
      return replacer;
    }
    // if both nodes exist, use left max value as per program requirement
    else if (node->left && node->right) {
      Node* maxNode = getMaxNode(node->left);

      // replace this node data with maxNode
      node->data = maxNode->data;

      // now that the data is replaced, delete that node.
      node->left = del(node->left, maxNode->data->name);
      return node;
    }
    // leaf node
    else {
      free(node);
      return NULL;
    }
  }
  // if target node is not found, keep looking
  else {
    // traverse according to BST rules
    if (compareBST(node, name) > 0) {
      node->left = del(node->left, name);
    } else {
      node->right = del(node->right, name);
    }
  }

  return node;
};

// returns the number of nodes 'smaller' than target node
int countSmaller(Node* node, char* name, int count) {
  if (!node) return count;

  // this node is larger than target node
  if (compareBST(node, name) > 0) {
    // continue looking
    return countSmaller(node->left, name, count);
  }
  // this node is smaller than target node
  else if (compareBST(node, name) < 0) {
    // then everything on its left is smaller than target, if there is any
    if (node->left) count += node->left->size;

    // continue looking; count + 1 to include this node.
    return countSmaller(node->right, name, count + 1);
  }
  // target node found
  else {
    // then everything on its left is smaller than target, if there is any
    if (node->left) count += node->left->size;
    return count;
  }
};

// merge divided arrays into one.
// Points in descending order; ties are broken by name in ascending order.
void merge(Customer* arr[], int lStart, int rStart, int end) {
  int len = end - lStart + 1;

  // temporary array to store sorted portion
  Customer** merged = calloc(len, sizeof(Customer*));

  int left = lStart;
  int right = rStart;
  int mergeIndex = 0;

  // Here we copy values into our auxiliary array, so long as there are
  // numbers from both lists to copy.
  while ((left < rStart) || (right <= end)) {
    // check if either list is exhausted and mark as NULL if they are
    Customer* lCustomer = left < rStart ? arr[left] : NULL;
    Customer* rCustomer = right <= end ? arr[right] : NULL;

    // if no sides are exhausted and have same points, sort by ascending name.
    if (lCustomer && rCustomer && compareMerge(lCustomer, rCustomer) == 0) {
      // compare name order and push in ascending order

      // left comes first
      if (strcmp(lCustomer->name, rCustomer->name) < 0) {
        merged[mergeIndex] = lCustomer;
        left++;
      }
      // right comes first
      else {
        merged[mergeIndex] = rCustomer;
        right++;
      }
    }
    // if right side is exhausted or
    // left side exists and its point is larger than right side
    else if (!rCustomer ||
             (lCustomer && compareMerge(lCustomer, rCustomer) > 0)) {
      merged[mergeIndex] = lCustomer;
      left++;
    }
    // left side is exhausted or
    // right side exists and its point is larger than left side
    else {
      merged[mergeIndex] = rCustomer;
      right++;
    }

    mergeIndex++;
  }

  // Copy back all of our values into the original array.
  for (int i = lStart; i <= end; i++) arr[i] = merged[i - lStart];

  // clean up
  free(merged);
}

// Recursive merge sort of customers
// Points in descending order; ties are broken by name in ascending order.
void mergeSort(Customer* customerArray[], int start, int end) {
  // Done size 0 or 1.
  if (start >= end) return;

  // mid point
  int m = (start + end) / 2;

  // sort left half
  mergeSort(customerArray, start, m);
  // sort right half
  mergeSort(customerArray, m + 1, end);

  // actually merge and sort
  merge(customerArray, start, m + 1, end);
}

// creates an inorder array from BST and free nodes when used up.
// index is referenced so recursive calls can track its increments.
void inorder(Node* node, Customer** arr, int* i) {
  if (node == NULL) return;

  inorder(node->left, arr, i);  // left
  arr[*i] = node->data;         // push root
  (*i)++;
  inorder(node->right, arr, i);  // right

  // no longer needed.
  free(node);
}

// process commands
int process(char command[], char name[], Node* root) {
  int points = 0;

  // since all commands start with a unique char (except search and sub),
  // we can check the first char instead of the whole string
  switch (command[0]) {
    // search or sub
    case 's':
      // search
      if (command[1] == 'e') search(root, name);
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
      // see if customer exists first
      Node* node = getNode(root, name);

      // if customer exists, delete
      if (node) {
        Customer* customer = node->data;

        del(root, name);

        // free target customer; this can't be done inside del as the
        // recursive call would free customer replacing the target as well
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
      // check if node exists
      Node* nodeToAdd = getNode(root, name);

      // if it exists, then add points to it
      if (nodeToAdd) {
        nodeToAdd->data->points += points;
        printf("%s %d", nodeToAdd->data->name, nodeToAdd->data->points);
      }
      // insert to tree otherwise
      else {
        insert(root, name, points);
      }
      break;
    case 't':
      test(getNode(root, name));
  }

  printf("\n");
}

int main() {
  int count;
  scanf("%d", &count);

  Node* root = calloc(1, sizeof(Node));

  for (int i = 0; i < count; i++) {
    char* command = calloc(1, (1 + COMMAND_MAX) * sizeof(char));
    char* name = calloc(1, (1 + NAME_MAX) * sizeof(char));
    scanf("%s %s", command, name);

    // process command
    process(command, name, root);
  }

  // array for final part of the answer
  Customer** customerArray = malloc(root->size * sizeof(Customer*));

  int index = 0;
  int size = root->size;

  // creates an inorder array from BST and free all nodes, including root.
  inorder(root, customerArray, &index);

  // sort the array
  mergeSort(customerArray, 0, size - 1);

  // final print loop
  for (int i = 0; i < size; i++) {
    Customer* customer = customerArray[i];
    printf("%s %d\n", customer->name, customer->points);

    // customer no longer needed
    free(customer);
  }

  // and now we don't need this
  free(customerArray);

  return 0;
}