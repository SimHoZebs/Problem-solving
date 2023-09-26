/* COP 3502C Assignment 2
This program is written by: Aisha Fathalla */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUES 13  // 13 because this program uses 1-indexing
#define MAX_CHARS 51

typedef struct Customer {
  char* name;
  int nOfTickets;
  int tOfArrival;
  int line;
} Customer;

typedef struct node {
  Customer* customerInfo;
  struct node* next;
} node;

typedef struct queue {
  node* front;
  node* back;
  int size;
} queue;

// functions prototype
Customer* createCustomer(char* this_name, int numTickets, int arrivalTime,
                         int line);
void initQueue(queue* q);
void enqueue(queue* q, Customer* newCustomer);
Customer* dequeue(queue* q);
Customer* peek(queue* q);
int isEmpty(queue* q);
int size(queue* q);
int assignQueue(char firstLetter, queue q[]);
void displayQueuesDebugging(queue q[]);
void processBooths(int b, int k, int usedQ[], queue q[]);
int processCustomer(queue* q, int boothMeetTime);
Customer* findNextCustomer(int firstQ, int operatedQnum, int usedQ[],
                           queue q[]);

int main() {
  // creates an array queues and initalizes each of them
  queue Q[MAX_QUEUES];
  for (int i = 0; i < MAX_QUEUES; i++) {
    initQueue(&Q[i]);
  }

  // reads in number of customers and booths
  int numCustomers, boothsCount, usedQueuesCount = 0;
  scanf("%i", &numCustomers);
  scanf("%i", &boothsCount);

  // loops through all the customers and adds them to queues
  for (int i = 0; i < numCustomers; i++) {
    // gets the customer info
    char name[MAX_CHARS];
    int numTickets, arrivalTime, line;
    scanf("%s", name);
    scanf("%i", &numTickets);
    scanf("%i", &arrivalTime);
    line = assignQueue(name[0], Q);

    // creates the customer and passes it to enqueue function to insert it
    Customer* newCustomer = createCustomer(name, numTickets, arrivalTime, line);
    enqueue(&Q[line], newCustomer);
  }

  // debugging line
  //  displayQueuesDebugging(Q);

  // loops through the queues and finds the number of non empty queues
  for (int i = 0; i < MAX_QUEUES; i++) {
    if (isEmpty(&Q[i]) == 0) usedQueuesCount++;
  }

  // debugging line
  // printf("%i queues are used \n", usedQueuesCount);

  // creates int array with numbers of used queues
  int usedQueues[usedQueuesCount];
  int j = 0;
  for (int i = 0; i < MAX_QUEUES; i++) {
    if (isEmpty(&Q[i]) == 0)
      if (j < usedQueuesCount) {
        usedQueues[j] = i;
        j++;
      }
  }

  // debugging line
  //    for (int i = 0; i < usedQueuesCount; i++){
  //        printf("%i, ", usedQueues[i]);
  //    }

  // calls a function to process booths and print output
  processBooths(boothsCount, usedQueuesCount, usedQueues, Q);

  return 0;
}

// initializes a queue with NULL front and back and size of 0
void initQueue(queue* q) {
  q->size = 0;  // no nodes yet, queue size is 0
  q->front = NULL;
  q->back = NULL;
}

// returns the queue number based on the customer's first letter
int assignQueue(char firstLetter, queue queue[MAX_QUEUES]) {
  // finds the position of the letter in the alphabet
  int p = firstLetter - 'A';
  int q = p % 13;  // given rule

  // if q is not zero, then q is the assigned queue
  if (q != 0) return q;

  // keeps track of the queue number that has least non-zero size
  int nonZeroMinQ = -1;

  // loops through the queues array and initializes nonZeroMinQ to the first
  // non-zero queue
  for (int i = 0; i < MAX_QUEUES; i++) {
    // if a non-zero size queue is found, the min is set to it, then the loop
    // breaks
    if (isEmpty(&queue[i]) == 0) {
      nonZeroMinQ = i;
      break;
    }
  }

  // if a non-zero queue was found, its size is compared to other non-zero
  // queues and min is updated
  if (nonZeroMinQ != -1) {
    for (int i = 0; i < MAX_QUEUES; i++) {
      if ((isEmpty(&queue[i]) == 0) &&
          (size(&queue[i]) < size(&queue[nonZeroMinQ])))
        nonZeroMinQ = i;
    }
    return nonZeroMinQ;  // the smallest non-zero queue number is returned
  }

  return 1;  // if no queue is filled yet, returns the first queue number
}

// returns the current number of customers in a queue;
int size(queue* q) { return q->size; }

// creates a new customer with passed values and returns a pointer to it
Customer* createCustomer(char* this_name, int numTickets, int arrivalTime,
                         int line) {
  // dynamically allocates memory for the new customer
  Customer* newCustomer = malloc(sizeof(Customer));

  // allocates memory for the name string and copies it to the customer name
  newCustomer->name = malloc((strlen(this_name) + 1) * sizeof(char));
  strcpy(newCustomer->name, this_name);

  // assigns passed values to corresponding costumer's info
  newCustomer->nOfTickets = numTickets;
  newCustomer->line = line;
  newCustomer->tOfArrival = arrivalTime;

  // returns a pointer to the new customer
  return newCustomer;
}

// adds the customer to the end of their queue
void enqueue(queue* q, Customer* newCustomer) {
  // creates a new node that points to the new customer
  node* newNode = malloc(sizeof(node));
  newNode->customerInfo = newCustomer;
  newNode->next = NULL;

  // increments the queue size by 1
  (q->size)++;

  // if queue is empty, set both front
  if (isEmpty(q) == 1) {
    q->front = newNode;
    q->back = newNode;
    return;
  }

  // if the queue is not empty, the back is updated
  q->back->next = newNode;
  q->back = newNode;
}

// returns 1 if queue is Empty and 0 if not.
int isEmpty(queue* q) {
  // if there is nothing in the queue front will point to NULL
  if (q->front == NULL && q->back == NULL)
    return 1;
  else
    return 0;
}

// debugging line
void displayQueuesDebugging(queue* q) {
  for (int i = 0; i < MAX_QUEUES; i++) {
    if (size(&q[i]) != 0) {
      for (int j = 0; j < q[i].size; j++) {
        printf("name: %s  tickets: %i  arrival time: %i  line: %i\n",
               q[i].front->customerInfo->name,
               q[i].front->customerInfo->nOfTickets,
               q[i].front->customerInfo->tOfArrival,
               q[i].front->customerInfo->line);
        q[i].front = q[i].front->next;
      }
    }
  }
}

void processBooths(int b, int k, int usedQ[], queue q[]) {
  // helping variables to implement booths concept
  int currentTime = 0;
  int currentQstart = 0;
  int totCostumers = 0;
  int extra = k % b;
  int operatedQNum;

  // assigns the booth the num of queues operated by it
  for (int i = 0; i < b; i++) {
    if (i < extra)
      operatedQNum = (k / b) + 1;
    else
      operatedQNum = (k / b);

    // finds the total number of customers a booth will process
    for (int j = currentQstart; j < (currentQstart + operatedQNum); j++) {
      totCostumers += size(&q[usedQ[j]]);
    }

    printf("Booth %i\n", i + 1);
    for (int j = 0; j < totCostumers; j++) {
      int nextQ = currentQstart, boothMeetTime = 0;
      Customer* nextCustomer = findNextCustomer(nextQ, operatedQNum, usedQ, q);

      if (nextCustomer != NULL) {
        nextQ = nextCustomer->line;

        if (nextCustomer->tOfArrival < currentTime)
          boothMeetTime = currentTime;
        else
          boothMeetTime = nextCustomer->tOfArrival;
      }

      // debugging lines
      currentTime = processCustomer(&q[nextQ], boothMeetTime);
    }

    totCostumers = 0;
    currentTime = 0;
    currentQstart += operatedQNum;
    printf("\n");
  }
}

Customer* findNextCustomer(int firstQ, int operatedQnum, int usedQ[],
                           queue q[]) {
  int size = operatedQnum;
  int minTime = 1e9;
  Customer* firstCustomer = NULL;

  for (int i = 0; i < size; i++) {
    Customer* nextCustomer = peek(&q[usedQ[firstQ + i]]);
    if (nextCustomer != NULL && minTime > nextCustomer->tOfArrival) {
      minTime = nextCustomer->tOfArrival;
      firstCustomer = nextCustomer;
    }
  }

  return firstCustomer;
}

int processCustomer(queue* q, int boothMeetTime) {
  int checkOutTime;
  Customer* customer = dequeue(q);

  if (customer != NULL) {
    checkOutTime = boothMeetTime + (30 + 5 * (customer->nOfTickets));

    printf("%s from line %i checks out at time %i.\n", customer->name,
           customer->line, checkOutTime);

    free(customer->name);
    free(customer);
  }
  return checkOutTime;
}

Customer* dequeue(queue* q) {
  if (q->front == NULL && q->back == NULL) return NULL;

  Customer* save = q->front->customerInfo;
  node* temp = q->front;
  q->front = q->front->next;
  free(temp);

  (q->size)--;

  return save;
}

Customer* peek(queue* q) {
  if (q->front == NULL) return NULL;

  return q->front->customerInfo;
}