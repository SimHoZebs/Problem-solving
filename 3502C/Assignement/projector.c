#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a projector.c -lm && ./a
./a < ./input.md > ./output.md
*/

typedef struct Group {
  double rad;
  int size;
} Group;

void merge(Group groupArr[], int start, int mid, int end) {
  int length = end - start + 1;
  Group* temp = calloc(length, sizeof(Group));

  int count1 = start;
  int count2 = mid;

  int mc = 0;
  while ((count1 < mid) || (count2 <= end)) {
    if (count2 > end ||
        (count1 < mid && groupArr[count1].rad < groupArr[count2].rad)) {
      temp[mc] = groupArr[count1];
      count1++;
      mc++;
    } else {
      temp[mc] = groupArr[count2];
      count2++;
      mc++;
    }
  }

  for (int i = start; i <= end; i++) groupArr[i] = temp[i - start];

  free(temp);
}

void mergeSort(Group groupArray[], int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;

    mergeSort(groupArray, start, mid);
    mergeSort(groupArray, mid + 1, end);

    merge(groupArray, start, mid, end);
  }
}

void printArray(Group* A, int size) {
  int i;
  for (i = 0; i < size; i++) printf("%lf ", A[i].rad);
  printf("\n");
}

int main() {
  double pi = acos(-1.0);
  int count;
  double angle;
  scanf("%d %lf", &count, &angle);
  angle = angle * (pi / 180);
  printf("Angle is: %lf\n", angle);

  Group* groupArray = malloc(sizeof(Group) * count);
  for (int i = 0; i < count; i++) {
    int x, y;
    scanf("%d %d %d", &x, &y, &groupArray[i].size);
    double rad = atan2(y, x);

    // go up to 2pi instead of -pi and pi
    if (rad < 0) rad = pi - rad;

    groupArray[i].rad = rad;
  }

  printArray(groupArray, count);
  mergeSort(groupArray, 0, count - 1);
  printArray(groupArray, count);

  return 0;
}