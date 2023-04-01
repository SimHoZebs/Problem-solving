//Ho Sim Gold#1
#include <stdio.h>
#include <stdlib.h>

int main() {
  int size;
  int **arr = malloc(size * sizeof(int *));

  for (int i = 0; i < size; i++) {
    arr[i] = malloc(size * sizeof(int));
  }

  scanf_s("%d", &size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      scanf_s("%d", &arr[i][j]);
    }
  }


  // the first row is the anchor
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[0][i];
  }

  // 012 = 345 = 678
  for (int i = 1; i < size; i++) {
    int testSum = 0;
    for (int j = 0; j < size; j++) {
      testSum += arr[i][j];
    }
    if (testSum != sum) {
      printf("Not equal\n");
      return 0;
    }
  }

  // 036 = 147 = 258
  for (int i = 0; i < size; i++) {
    int testSum = 0;
    for (int j = 0; j < size; j++) {
      testSum += arr[j][i];
    }
    if (testSum != sum) {
      printf("Not equal\n");
      return 0;
    }
  }

  // 048 = 245
  int testSum = 0;
  for (int i = 0; i < size; i++) {
    testSum += arr[i][i];
  }
  if (testSum != sum) {
    printf("Not equal\n");
    return 0;
  }

  int test2 = 0;
  for (int i = size-1; i>= 0; i--){
    test2 += arr[i][i];
  }
  if (test2 != sum) {
    printf("Not equal\n");
    return 0;
  }

  printf("Equal\n");

  return 0;
}
