#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc age.c -o a && ./a
*/

int main() {
  int aa, ak, ao;

  scanf("%d", &ao);
  scanf("%d", &aa);
  scanf("%d", &ak);

  int a, k;

  int highestMultiple = ao / aa;  // 6

  while (1) {
    if (highestMultiple == 0) {
      printf("%d", 0);
      break;
    };

    int k = (ao - highestMultiple * aa) / ak;
    int kRemainder = (ao - highestMultiple * aa) % ak;

    if (kRemainder == 0 && k != 0) {
      printf("%d", 1);
      break;
    } else {
      highestMultiple--;
    }
  }

  ao = a * aa + k * ak;

  return 0;
}