#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name {
  int field;
};

int main() {
  int n;
  struct name** list = calloc(n, sizeof(struct name*));

  for (int i = 0; i < n; i++) {
    list[i] = malloc(sizeof(struct name));
  }

  int j;
  int k;

  struct name* tmp = list[j];
  list[j] = list[k];
  list[k] = tmp;

  // same thing
  list[j]->field = 7;
  (*list[j]).field = 7;

  return 0;
}
//

int INIT_SIZE = 9;

typedef struct claim {
  int* claims;
  int maxSize;
  int currSize;
  long long sumCost;
} claim;

int dynamicList() { claim* list = malloc(sizeof(claim) * 10); }

claim* createItem() {
  claim* newItem = malloc(sizeof(claim));
  newItem->claims = calloc(INIT_SIZE, sizeof(int));
  newItem->currSize = 0;
  newItem->sumCost = 0;

  return newItem;
}

void addClaim(claim* claimPtr, int value) {
  if (claimPtr->currSize == claimPtr->maxSize) {
    claimPtr->claims =
        realloc(claimPtr->claims, 2 * claimPtr->maxSize * (sizeof(int)));
  }
}