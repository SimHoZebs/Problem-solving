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

    // if the list at this hash has no node, create a node for it.
    // since the assignment guarantees items' existence on change_price and sell
    // commands, this only occurrs on a buy command.
    if (hashtable.lists[hash] == NULL)
      hashtable.lists[hash] = calloc(1, sizeof(Node));

    // node is now guaranteed to exist
    Node* node = hashtable.lists[hash];

    // buy
    if (strcmp(command, "buy") == 0) {
      complexity++;
      int quantity, totalPrice;
      scanf("%d %d", &quantity, &totalPrice);

      // there is an item in this node but not the same item; conflict
      if (node->iPtr && strcmp(node->iPtr->name, itemName) != 0) {
        // traverse through linked list until we reach the last node
        while (node->next != NULL) {
          complexity++;
          node = node->next;
        }

        // create and link nextNode
        node->next = calloc(1, sizeof(Node));

        // assign this last node as the node we will be working with
        node = node->next;
      }

      // if there is no item in this node
      if (!node->iPtr) {
        // create item
        Item* item = calloc(1, sizeof(Item));
        strcpy(item->name, itemName);
        item->quantity = quantity;
        item->salePrice = totalPrice / quantity;

        // insert the item in node
        node->iPtr = item;
      }
      // there is an item in this node and it's the same item!
      else {
        printf("---Item found, quantity is %d, adding %d\n",
               node->iPtr->quantity, quantity);
        // just increase the quantity
        node->iPtr->quantity += quantity;
      }

      budget -= totalPrice;
    }
    // sell
    else if (strcmp(command, "sell") == 0) {
      complexity++;
      int quantity;
      scanf("%d", &quantity);

      // item is guaranteed to be in the inventory, so no NULL check for the
      // node.
      Item* item = node->iPtr;

      // if not the item we are looking for, traverse the linked list.
      while (strcmp(item->name, itemName) != 0) {
        complexity++;
        item = node->next->iPtr;
        node = node->next;
      }

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
      complexity++;
      int newPrice;
      scanf("%d", &newPrice);

      // item is guaranteed to be in the inventory, meaning this pointer is
      // never NULL.
      Item* item = node->iPtr;

      // traverse linked list until we find the right item
      while (strcmp(item->name, itemName) != 0) {
        complexity++;
        item = node->next->iPtr;
        node = node->next;
      }

      // change price
      item->salePrice = newPrice;
    }

    if (strcmp(command, "change_price") != 0) {
      Item* item = node->iPtr;

      printf("%s %d %d\n", item->name, item->quantity, budget);
    }
  }

  printf("%d\n", budget);
  printf("%d\n", complexity);

  return 0;
}