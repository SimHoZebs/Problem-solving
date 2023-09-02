#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc window.c -o a && ./a
*/

void swap(int* xp, int* yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(int arr[], int startIndexArr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int minValIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minValIndex] ||
          (arr[j] == arr[minValIndex] && j > minValIndex)) {
        minValIndex = j;
      }
    }

    int tmp = startIndexArr[minValIndex];
    startIndexArr[minValIndex] = i;
    startIndexArr[i] = tmp;

    swap(&arr[minValIndex], &arr[i]);
  }
}

int main() {
  int size, len;

  scanf("%d", &size);
  scanf("%d", &len);
  int* arr = calloc(size, sizeof(int));

  int* value = calloc(size - len + 1, sizeof(int));
  int* startIndexArr = calloc(size - len + 1, sizeof(int));

  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }

  for (int i = 0; i < size - len + 1; i++) {
    startIndexArr[i] = i;
    for (int j = 0; j < len; j++) {
      value[i] = value[i] + (j + 1) * arr[i + j];
    }
  }

  selectionSort(value, startIndexArr, size - len + 1);

  for (int i = 0; i < size - len + 1; i++) {
    printf("%d %d\n", startIndexArr[i] + 1, value[i]);
  }

  return 0;
}