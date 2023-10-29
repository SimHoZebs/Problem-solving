/**
 * HO SIM
 * movieline.c
 * 25th SEP 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a p2.c -lm && ./a
./a < input.md > output.md
*/

#define MAX_QUEUE_COUNT 13

typedef struct Customer {
  char* name;
  int ticketCount;
  int lineNumber;
  int arrivalTime;
} Customer;

typedef struct Node {
  Customer* customer;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* front;
  Node* back;
  int size;
} Queue;

// Doesn't look any better than queue->size, but I'm required to use it.
int size(Queue* queue) { return queue->size; }

// required function
Node* peek(Queue* queue) { return queue->front; }

// size() returning 0 is falsy and every other value is truthy, but...
int isEmpty(Queue* queue) { return size(queue) ? 0 : 1; }

/**
 * add customer to back of node; front as well if queue is empty
 */
void enqueue(Queue* queue, Customer* customer) {
  Node* newNode = malloc(sizeof(Node));

  newNode->customer = customer;

  if (isEmpty(queue)) {
    // first node of queue, so it is both front and back of queue.
    queue->front = newNode;
    queue->back = newNode;
  } else {
    queue->back->next = newNode;
    queue->back = newNode;
  }

  queue->size += 1;
}

/**
 * swap queue's front with its next node and free the previous front.
 */
void dequeue(Queue* queue) {
  Node* temp = peek(queue)->next;

  // free memory for the front node, but NOT free memory for the customer.
  free(queue->front);

  queue->front = temp;
  queue->size--;
}

/*
 * Create a customer.
 */
Customer* createCustomer(char* name, int ticketCount, int arrivalTime,
                         int lineNumber) {
  Customer* customer = malloc(sizeof(Customer));

  int nameLen = strlen(name);
  customer->name = malloc(nameLen * sizeof(char));

  strcpy(customer->name, name);
  customer->ticketCount = ticketCount;
  customer->arrivalTime = arrivalTime;
  customer->lineNumber = lineNumber;

  return customer;
}

/**
 * loops through all queues and compares their size
 * @returns index of the smallest queue
 */
int getShortestQueueIndex(Queue** queueArray) {
  int smallestSize = 0;
  // index for if all queue sizes are 0
  int index = 1;

  for (int i = 0; i < MAX_QUEUE_COUNT; i++) {
    if (!queueArray[i]) continue;

    Queue* queue = queueArray[i];
    int queueSize = size(queue);

    if (!smallestSize) {
      smallestSize = queueSize;
      index = i;
    } else if (!(isEmpty(queue)) && queueSize < smallestSize) {
      // if not 0 and smaller than recorded size
      smallestSize = queueSize;
      index = i;
    }
  }
  return index;
}

/**
 * @param boothIntake number of queues the booth is to serve.
 * @param startIndex the index of the first queue the booth should check to
 * serve.
 * @param endIndex the index of the last queue the booth should check to
 * serve.
 * @returns -1 when there is no queue to serve; otherwise the queue index to
 * serve.
 */
int getQueueIndexToServe(Queue** queueArray, int boothIntake, int* startIndex) {
  // number of queues checked to service
  int queueCount = 0;
  int indexToServe = -1;

  int tmpStartIndex = *startIndex;

  // keep checking queues for a customer at front with the smallest
  // arrivalTime until we've checked as many queues as the booth can serve.
  for (int i = tmpStartIndex; i < MAX_QUEUE_COUNT && queueCount < boothIntake;
       i++) {
    // if queue doesn't exist, skip
    if (!queueArray[i]) continue;

    // empty queues are ones exhausted by the booth, so they count, but skipped.
    if (isEmpty(queueArray[i])) {
      queueCount++;
      continue;
    }

    // otherwise this queue is valid to compare.
    queueCount++;
    // if this is the final queue to process, update endQueueIndex to be aware
    // for future loops

    Queue* queue = queueArray[i];

    if (indexToServe < 0 ||
        peek(queueArray[indexToServe])->customer->arrivalTime >
            peek(queue)->customer->arrivalTime) {
      indexToServe = i;
    }
  }

  if (*startIndex < 1) *startIndex = tmpStartIndex;

  return indexToServe;
}

int main() {
  int customerCount, boothCount;

  scanf("%d %d", &customerCount, &boothCount);

  // initialize 13 queue pointers; index 0 is useless
  Queue** queueArray = malloc(MAX_QUEUE_COUNT * sizeof(Queue*));

  // number of valid queues in queueArray
  int queueCount = 0;

  for (int i = 0; i < customerCount; i++) {
    char name[50];
    int ticketCount, time;

    scanf("%s %d %d", name, &ticketCount, &time);

    // find queueNum to assign the customer to
    int queueNum = (name[0] - 'A') % MAX_QUEUE_COUNT;
    if (!queueNum) queueNum = getShortestQueueIndex(queueArray);

    // make queue when queue doesn't exist
    if (!queueArray[queueNum]) {
      queueArray[queueNum] = malloc(sizeof(Queue));
      queueCount++;
    }

    Customer* customer = createCustomer(name, ticketCount, time, queueNum);
    enqueue(queueArray[queueNum], customer);
  }

  int remainder = queueCount % boothCount;

  int startQueueIndex = 0;

  for (int i = 0; i < boothCount; i++) {
    // reference for which queue index the next booth should start checking
    int endQueueIndex = 0;

    // amount of time passed on this booth
    int currTime = 0;
    printf("Booth %d\n", i + 1);

    // number of queues this booth can handle
    int boothIntake = queueCount / boothCount;
    if (i < remainder) boothIntake++;

    int queueIndex = 0;
    while (queueIndex >= 0) {
      queueIndex =
          getQueueIndexToServe(queueArray, boothIntake, &startQueueIndex);

      // queueIndex is -1 when tere is no queue left to serve
      if (queueIndex < 0) {
        for (int i = startQueueIndex; i < endQueueIndex + 1; i++) {
          if (queueArray[i]) free(queueArray[i]);
        }

        printf("\n");
        break;
      }

      // update endQueueIndex to the 'largest' queue index
      if (queueIndex > endQueueIndex) endQueueIndex = queueIndex;

      Queue* queue = queueArray[queueIndex];

      Customer* customer = peek(queue)->customer;
      // if customer arrived later than current time, arrival time is current
      // time
      if (currTime < customer->arrivalTime) currTime = customer->arrivalTime;

      currTime += 30 + customer->ticketCount * 5;

      dequeue(queue);

      printf("%s from line %d checks out at time %d.\n", customer->name,
             customer->lineNumber, currTime);

      // free customer data
      free(customer->name);
      free(customer);
    }

    // making next booths to start checking queues 'larger' than this booth.
    startQueueIndex = endQueueIndex + 1;
  }

  free(queueArray);

  return 0;
}