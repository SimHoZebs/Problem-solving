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

// merge divided arrays into one.
void merge(Group arr[], int lStart, int rStart, int end) {
  int len = end - lStart + 1;

  // array to store sorted portion
  Group* tmp = calloc(len, sizeof(Group));

  int left = lStart;
  int right = rStart;
  int mergeIndex = 0;

  while ((left < rStart) || (right <= end)) {
    if (right > end || (left < rStart && arr[left].rad < arr[right].rad)) {
      tmp[mergeIndex] = arr[left];
      left++;
    } else {
      tmp[mergeIndex] = arr[right];
      right++;
    }
    mergeIndex++;
  }

  // Copy back all of our values into the original array.
  for (int i = lStart; i <= end; i++) arr[i] = tmp[i - lStart];

  // clean up
  free(tmp);
}

void mergeSort(Group* groupArray, int start, int end) {
  if (start < end) {
    int m = (start + end) / 2;

    // recursively divide from middle
    mergeSort(groupArray, start, m);
    mergeSort(groupArray, m + 1, end);

    // actually merge and sort
    merge(groupArray, start, m + 1, end);
  }
}

int main() {
  double pi = acos(-1.0);
  int count;
  double angle;
  scanf("%d %lf", &count, &angle);
  // convert angle to radian
  angle = angle * (pi / 180);

  // size is double the count to store a copy of each group with diff radian
  Group* groupArray = malloc(sizeof(Group) * count * 2);
  for (int i = 0; i < count; i++) {
    int x, y;
    scanf("%d %d %d", &x, &y, &groupArray[i].size);
    double rad = atan2(y, x);

    // go up to 2pi instead of -pi and pi
    if (rad < 0) rad = pi - rad;

    groupArray[i].rad = rad;

    // storing a copy with 2*pi more rad to emulate circular sweep
    groupArray[i + count].rad = rad + 2 * pi;
    groupArray[i + count].size = groupArray[i].size;
  }

  // sort groups by radian
  mergeSort(groupArray, 0, (count * 2) - 1);

  int minPeopleCount = -1;
  double maxDistance = 0;
  // compare groups' radial distance with projection's radian
  for (int i = 0; i < count; i++) {
    // if previous comparison found no people in projection, no more check is
    // necessary.
    if (minPeopleCount == 0) break;

    // store largest group radial distance diff
    if (groupArray[i + 1].rad - groupArray[i].rad > maxDistance) {
      maxDistance = groupArray[i + 1].rad - groupArray[i].rad;
    }

    // the projection radian excluding the current group
    double tempRad = groupArray[i].rad + (1 * pi / 180) + angle;

    int inProjectionCount = 0;
    // check what groups are in this projection
    for (int j = i + 1; j < count * 2; j++) {
      if (groupArray[j].rad > tempRad) break;
      inProjectionCount += groupArray[j].size;
    }

    // store the minimum number of people in projection
    if (minPeopleCount < 0 || inProjectionCount < minPeopleCount) {
      minPeopleCount = inProjectionCount;
    }
  }

  // output answers
  printf("%d\n", minPeopleCount);
  printf("%.4lf\n", maxDistance * (180 / pi));

  // clean up
  free(groupArray);

  return 0;
}