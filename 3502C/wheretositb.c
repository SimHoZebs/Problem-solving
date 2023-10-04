/*
HO SIM
wheretositb.c
3 OCT 2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a wheretositb.c -lm && ./a
./a < ./input.md > ./output.md
*/

#define MAX_NAME_LEN 20
#define MAX_ATTENDEE_COUNT 10

typedef struct Attendee {
  char name[MAX_NAME_LEN];
  int hasPopCorn;
  int* avoidArray;
} Attendee;

int isValid(Attendee* attendeeArray, int attendeeCount, int* permutation) {
  // whether previous attendee had popcorn; used to check if next attendee must
  // have a popcorn or not
  int prevHadPopcorn = -1;
  int prevIndex = -1;
  // whether the attendee must have popcorn; boolean that confirms whether the
  // permutation is valid or not
  int mustHavePopcorn = -1;

  for (int i = 0; i < attendeeCount; i++) {
    Attendee attendee = attendeeArray[permutation[i]];

    // if previous attendee's index is found in attendee's avoidArray
    if (prevIndex != -1 && attendee.avoidArray[prevIndex]) {
      return 0;
    }

    // if mustHavePopcorn is unassigned, assign the reverse value of hasPopcorn.
    // if attendee has popcorn, next person isn't required to have popcorn.
    if (mustHavePopcorn == -1 || attendee.hasPopCorn) {
      mustHavePopcorn = attendee.hasPopCorn ? 0 : 1;
    } else {
      // if attendee has no popcorn and must have it, permutation is invalid.
      if (mustHavePopcorn) return 0;

      // if attendee has no popcorn, isn't required to have it, and previous
      // attendee doesn't have popcorn...
      if (!prevHadPopcorn) {
        //...but is the last attendee, permutation is invalid.
        if (i + 1 == attendeeCount) return 0;
        //...but isn't the last attendee, the next attendee must have popcorn.
        mustHavePopcorn = 1;
      } else {
        // if attendee has no popcorn, isn't required to have it, but previous
        // attendee had popcorn, next attendee isn't required to have popcorn.
        mustHavePopcorn = 0;
      }
    }

    prevHadPopcorn = attendee.hasPopCorn;
    prevIndex = permutation[i];
  }

  return 1;
}

int perm(Attendee* attendeeArray, int* permutation, int* used,
         int attendeeCount, int index) {
  if (index == attendeeCount) {
    if (!isValid(attendeeArray, attendeeCount, permutation)) return 0;

    // print first valid permutation
    for (int i = 0; i < attendeeCount; i++) {
      printf("%s\n", attendeeArray[permutation[i]].name);
    }
    return 1;
  }

  for (int i = 0; i < attendeeCount; i++) {
    if (used[i]) continue;

    used[i] = 1;
    permutation[index] = i;
    if (perm(attendeeArray, permutation, used, attendeeCount, index + 1))
      return 1;
    used[i] = 0;
  }

  return 0;
}

// compare names of all attendees until a match is found. return -1 is not
// found.
int findIndexByName(Attendee* attendeeArray, int attendeeCount, char* name) {
  int index = -1;
  for (int i = 0; i < attendeeCount; i++) {
    if (!strcmp(attendeeArray[i].name, name)) {
      index = i;
      break;
    }
  }
  return index;
}

int main() {
  Attendee attendeeArray[MAX_ATTENDEE_COUNT];

  int attendeeCount, avoidPairCount;
  scanf("%d %d", &attendeeCount, &avoidPairCount);

  for (int i = 0; i < attendeeCount; i++) {
    scanf("%s %d", attendeeArray[i].name, &(attendeeArray[i].hasPopCorn));

    // dynamic allocation to init array with value 0
    attendeeArray[i].avoidArray = calloc(attendeeCount, sizeof(int));
  }

  for (int i = 0; i < avoidPairCount; i++) {
    char name1[MAX_NAME_LEN], name2[MAX_NAME_LEN];
    scanf("%s %s", name1, name2);
    int attendee1Index = findIndexByName(attendeeArray, attendeeCount, name1);
    int attendee2Index = findIndexByName(attendeeArray, attendeeCount, name2);

    // if attendees are not found in attendeeArray; this should never happen
    if (attendee1Index == -1 || attendee2Index == -1) return 0;

    // assign truth values to index of attendees to avoid
    attendeeArray[attendee1Index].avoidArray[attendee2Index] = 1;
    attendeeArray[attendee2Index].avoidArray[attendee1Index] = 1;
  }

  // static initialization of 0'd arrays
  int permutated[MAX_ATTENDEE_COUNT] = {0};
  int permutation[MAX_ATTENDEE_COUNT] = {0};
  perm(attendeeArray, permutation, permutated, attendeeCount, 0);

  for (int i = 0; i < attendeeCount; i++) {
    free(attendeeArray[i].avoidArray);
  }
  return 0;
}