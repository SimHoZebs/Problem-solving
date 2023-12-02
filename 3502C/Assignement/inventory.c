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

// find the node we should be working with.
Node* findNode(Node* node, char itemName[], int* complexity) {
  // no item on this node
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

  for (int i = 0; i < commandCount; i++) {
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

      // this node has the item
      if (node->iPtr && strcmp(node->iPtr->name, itemName) == 0) {
        complexity++;
        node->iPtr->quantity += quantity;
      }
      // this node has an item but not the one we are looking for
      else if (node->iPtr) {
        // look for the item's node
        Node* itemNode = findNode(node, itemName, &complexity);

        // if item exists in this linked list
        if (itemNode) {
          itemNode->iPtr->quantity += quantity;
          node = itemNode;
        }
        // item doesn't exist
        else {
          // add a new node to the front of the linked list
          Node* newNode = calloc(1, sizeof(Node));
          hashtable.lists[hash] = newNode;

          // put the current node as the next node of this new node
          newNode->next = node;

          // setting the new node as the node to continue working with
          node = newNode;
        }
      }

      // this node never had an item
      if (!node->iPtr) {
        // increasing linked list length = complexity++
        complexity++;

        // creating item
        Item* item = calloc(1, sizeof(Item));
        strcpy(item->name, itemName);
        item->quantity = quantity;
        item->salePrice = totalPrice / quantity;

        // assigning item to this node
        node->iPtr = item;
      }

      budget -= totalPrice;
    }
    // sell
    else if (strcmp(command, "sell") == 0) {
      // assignment guarantees that node is never NULL for sell
      node = findNode(node, itemName, &complexity);
      int quantity;
      scanf("%d", &quantity);

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

  return 0;
}