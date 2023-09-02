#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc q1.c -o a && ./a
*/

int main() {
  int s1;
  int s2;
  scanf("%d", &s1);
  scanf("%d", &s2);

  if (s1 * 2 >= s2) {
    printf("E");
  } else {
    printf("H");
  }

  return 0;
}