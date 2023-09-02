#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc q3.c -o a && ./a
*/

int main() {
  int len;
  scanf("%d", &len);
  int *arr = malloc(sizeof(int) * len);

  int count = 1;

  for (int i = 0; i < len; i++) {
    scanf("%d", &arr[i]);
  }

  for (int i = 0; i < len; i++) {
    int tmpCount = 1;

    int tmpStart = arr[i];

    for (int j = i + 1; j < len; j++) {
      if (arr[j] - arr[j - 1] > 0) {
        tmpCount++;
      } else {
        break;
      }
    }

    if (tmpCount > count) {
      count = tmpCount;
    }
  }

  printf("%d", count);

  return 0;
}