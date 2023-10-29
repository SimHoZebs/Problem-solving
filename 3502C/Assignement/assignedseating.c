/*
 * Ho Sim
 * assignedseatig.c
 * 11 SEP 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a assignedseating.c -lm && ./a
type ./input.md | ./a.exe > ./output.md
*/
#define INITSIZE 10
#define MAXLEN 50
#define MAXROWS 100000

typedef struct order {
  int s_seat;
  int e_seat;
  char* name;
} order;

typedef struct theaterRow {
  order** list_orders;
  int max_size;
  int cur_size;
} theaterRow;

// Returns a pointer to a dynamically allocated order storing the given
// start row, end row, and the name this_name. Note: strcpy should be
// used to copy the contents into the struct after its name field is
// dynamically allocated.
order* make_order(int start, int end, char* this_name) {
  // dma for order
  order* newOrder = malloc(sizeof(order));

  // struct value assignment
  newOrder->s_seat = start;
  newOrder->e_seat = end;
  newOrder->name = this_name;

  return newOrder;
};

// This function will allocate the memory for one theaterrow, including
// allocating its array of orders to a default maximum size of 10, and
// setting its current size to 0.
theaterRow* make_empty_row() {
  // dma for theater
  theaterRow* newTheaterRow = malloc(sizeof(theaterRow));

  // struct value assignment
  newTheaterRow->list_orders = calloc(INITSIZE + 1, sizeof(order*));
  newTheaterRow->max_size = INITSIZE;
  newTheaterRow->cur_size = 0;

  return newTheaterRow;
};

// Assuming that order1 and order2 point to orders on the same row, this
// function returns 1 if the orders conflict, meaning that they share // at
// least 1 seat in common, and returns 0 otherwise.
int conflict(order* order1, order* order2) {
  // comparing end and start seats of orders; s_seat being larger than e_seat
  // guarantees no seat intersects
  if (order1->s_seat > order2->e_seat || order2->s_seat > order1->e_seat)
    return 0;

  return 1;
};

// Returns 1 if the order pointed to by this_order can be added to the
// row pointed to by this_row. Namely, 1 is returned if and only if
// this_order does NOT have any seats in it that are part of any order
// already on this_row.
int can_add_order(theaterRow* this_row, order* this_order) {
  // check for conflict on each order
  for (int i = 0; i < this_row->cur_size; i++) {
    if (conflict(this_order, this_row->list_orders[i])) return 0;
  }

  return 1;
};

// This function tries to add this_order to this_row. If successful,
// the order is added and 1 is returned. Otherwise, 0 is returned and
// no change is made to this_row. If the memory for this_row is full,
// this function will double the maximum # of orders allocated for the
// row (via realloc), before adding this_order, and adjust max_size and
// cur_size of this_row.
int add_order(theaterRow* this_row, order* this_order) {
  int maxSize = this_row->max_size;

  if (can_add_order(this_row, this_order)) {
    // if array is full
    if (this_row->cur_size >= maxSize) {
      this_row->list_orders = realloc(this_row->list_orders, maxSize * 2);

      this_row->max_size = maxSize * 2;
    }

    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
    return 1;
  }

  return 0;
};

// This function returns 1 if the seat number seat_no is contained in
// the range of seats pointed to by myorder, and returns 0 otherwise.
int contains(order* myorder, int seat_no) {
  // seat exists between order if seat_no is a value between s_seat and e_seat
  if (myorder->s_seat <= seat_no && seat_no <= myorder->e_seat) return 1;

  return 0;
};

// If seat_num in the row pointed to by this_row is occupied, return a
// pointer to the string storing the owner’s name. If no one is sitting
// in this seat, return NULL.
char* get_row_owner(theaterRow* this_row, int seat_num) {
  // check if seat_num is within each order
  for (int i = 0; i < this_row->cur_size; i++) {
    if (contains(this_row->list_orders[i], seat_num)) {
      return this_row->list_orders[i]->name;
    }
  }
  return NULL;
};

// If seat_num seat number in row number row is occupied, return a
// pointer to the owner’s name. Otherwise, return NULL.
char* get_owner(theaterRow** theater, int row, int seat_num) {
  return get_row_owner(theater[row], seat_num);
};

// Frees all memory associated with this_order.
void free_order(order* this_order) {
  free(this_order->name);
  free(this_order);
};

// Frees all memory associated with this_row.
void free_row(theaterRow* this_row) {
  for (int j = 0; j < this_row->cur_size; j++) {
    free_order(this_row->list_orders[j]);
  }
  free(this_row);
};

int main() {
  // initialize theater
  theaterRow** amc = calloc(MAXROWS + 1, sizeof(theaterRow*));
  for (int i = 0; i < MAXROWS + 1; i++) {
    amc[i] = make_empty_row();
  }

  while (1) {
    // receive input
    char* command = malloc(sizeof(char) * 8);
    scanf("%s", command);

    if (!strcmp(command, "QUIT")) {
      // clean up
      for (int i = 0; i < MAXROWS; i++) {
        free_row(amc[i]);
      }
      free(command);
      free(amc);
      break;
    }

    int row;
    scanf("%d", &row);

    if (!strcmp(command, "BUY")) {
      // parameters for BUY
      int start, end;
      char* name = malloc(sizeof(char) * MAXLEN);

      scanf("%d", &start);
      scanf("%d", &end);
      scanf("%s", name);

      order* newOrder = make_order(start, end, name);
      int result = add_order(amc[row], newOrder);

      // clean up unfulfilled order
      if (!result) free(newOrder);

      printf("%s\n", result ? "SUCCESS" : "FAILURE");

    } else if (!strcmp(command, "LOOKUP")) {
      // LOOKUP parameters
      int seat;
      scanf("%d", &seat);

      char* owner = get_owner(amc, row, seat);
      printf("%s\n", owner ? owner : "No one");
    }

    free(command);
  }

  return 0;
}
