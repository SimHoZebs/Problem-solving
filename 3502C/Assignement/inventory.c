/*
Ho Sim
inventory.c
2nd DEC 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a inventory.c -lm && ./a
stdbuf -i0 -o0 -e0 ./a < ./inventory_0.in > ./test.out
diff -y inventory_0.out test.out | tee diff.txt
*/

#define MAXLEN 19
#define TABLESIZE 300007
#define COMMAND_MAX 12

typedef struct Item {
  char name[MAXLEN + 1];
  int quantity;
  int salePrice;
} Item;

typedef struct Node {
  Item* iPtr;
  struct Node* next;
} Node;

typedef struct Hashtable {
  Node** lists;
  int size;
} Hashtable;

int hashfunc(char* word, int size) {
  int len = strlen(word);
  int res = 0;
  for (int i = 0; i < len; i++) res = (1151 * res + (word[i] - 'a')) % size;
  return res;
}

// find the node we should be working with. Return NULL if it doesn't exist.
Node* findNode(Node* node, char itemName[], int* complexity) {
  // no item on this node. Item node doesn't exist.
  if (!node->iPtr) return NULL;
  int len = 1;

  // if there is an item on this node, the item is at least the 1st in the
  // linked list.
  (*complexity)++;

  // if not the item we are looking for, traverse the linked list:
  while (strcmp(node->iPtr->name, itemName) != 0) {
    // if next is NULL, nowhere to traverse to. The item doesn't exist.
    if (node->next == NULL) {
      return NULL;
    }

    // traverse the linked list
    node = node->next;

    // then the item could be on the next node
    (*complexity)++;
    len++;
  }

  return node;
}

// create an item.
Item* createItem(char itemName[], int quantity, int totalPrice) {
  Item* item = calloc(1, sizeof(Item));
  strcpy(item->name, itemName);
  item->quantity = quantity;
  item->salePrice = totalPrice / quantity;

  return item;
}

// frees item, then the node.
void freeLinkedList(Node* node) {
  // Recursively free each element in the list.
  if (node != NULL) {
    Node* temp = node->next;
    freeLinkedList(temp);

    free(node->iPtr);
    free(node);
  }
}

int main() {
  // theater's budget described in assignment
  int budget = 100000;

  // total complexity
  int complexity = 0;

  // initializing hashtable
  Hashtable hashtable;
  hashtable.size = TABLESIZE;
  hashtable.lists = calloc(TABLESIZE, sizeof(Node*));

  // number of commands executed for this run
  int commandCount;
  scanf("%d", &commandCount);

  // command processing
  for (int i = 0; i < commandCount; i++) {
    // universal input
    char command[COMMAND_MAX + 1], itemName[MAXLEN + 1];
    scanf("%s %s", command, itemName);

    // hash and the node in question for this command
    int hash = hashfunc(itemName, TABLESIZE);

    // if there's no node at this hash, create one.
    // since items' are guaranteed to exist on change_price and sell commands,
    // this only occurrs on a buy command.
    if (!hashtable.lists[hash]) {
      hashtable.lists[hash] = calloc(1, sizeof(Node));
    }

    // node is now guaranteed to exist
    Node* node = hashtable.lists[hash];

    // buy
    if (strcmp(command, "buy") == 0) {
      int quantity, totalPrice;
      scanf("%d %d", &quantity, &totalPrice);

      // find the node this item exists in. May be NULL!
      Node* itemNode = findNode(node, itemName, &complexity);

      // item exists on a node
      if (itemNode) {
        // set itemNode as the node we are working with.
        node = itemNode;

        // then just increase the quantity
        node->iPtr->quantity += quantity;
      }
      // the item doesn't exist
      else {
        // if this node have an item,
        if (node->iPtr) {
          // add a new node to the front of the linked list
          Node* newNode = calloc(1, sizeof(Node));
          hashtable.lists[hash] = newNode;

          // put the current node as the next node of this new node
          newNode->next = node;

          // setting the new node as the node to continue working with
          node = newNode;
        }

        // whether this node has an item or not, this item must be created.
        //  increasing linked list length = complexity++
        complexity++;

        // create item and assign it to this node
        node->iPtr = createItem(itemName, quantity, totalPrice);
      }

      // wallet grows smaller
      budget -= totalPrice;
    }
    // sell
    else if (strcmp(command, "sell") == 0) {
      int quantity;
      scanf("%d", &quantity);

      // assignment guarantees that node is never NULL for sell
      node = findNode(node, itemName, &complexity);

      // so iPtr exists too
      Item* item = node->iPtr;

      // if requested quantity is larger than inventory, sell inventory
      if (item->quantity < quantity) {
        budget += item->quantity * item->salePrice;
        item->quantity = 0;
      }
      // otherwise sell requested quantity
      else {
        budget += quantity * item->salePrice;
        item->quantity -= quantity;
      }

    }
    // change_price
    else {
      // assignment guarantees that node is never NULL for change_price
      node = findNode(node, itemName, &complexity);
      int newPrice;
      scanf("%d", &newPrice);

      // change price
      node->iPtr->salePrice = newPrice;
    }

    // output for all commands but change_price
    if (strcmp(command, "change_price") != 0) {
      Item* item = node->iPtr;

      printf("%s %d %d\n", item->name, item->quantity, budget);
    }
  }

  printf("%d\n", budget);
  printf("%d\n", complexity);

  // free all linked list in each hash
  for (int i = 0; i < TABLESIZE; i++) {
    freeLinkedList(hashtable.lists[i]);
  }

  // free the hashtable
  free(hashtable.lists);

  return 0;
}