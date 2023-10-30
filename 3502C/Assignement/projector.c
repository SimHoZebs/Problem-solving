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

void merge(Group* groupArr, int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  Group L[n1], R[n2];

  for (i = 0; i < n1; i++) L[i] = groupArr[l + i];
  for (j = 0; j < n2; j++) R[j] = groupArr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i].rad <= R[j].rad) {
      groupArr[k] = L[i];
      i++;
    } else {
      groupArr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    groupArr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    groupArr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(Group* groupArray, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(groupArray, l, m);
    mergeSort(groupArray, m + 1, r);

    merge(groupArray, l, m, r);
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
  printf("count is: %d\n", count);

  // size is double the count to store 2 copies of group with rad diff of 2pi
  Group* groupArray = malloc(sizeof(Group) * count * 2);
  for (int i = 0; i < count; i++) {
    int x, y;
    scanf("%d %d %d", &x, &y, &groupArray[i].size);
    double rad = atan2(y, x);

    // go up to 2pi instead of -pi and pi
    if (rad < 0) rad = pi - rad;

    groupArray[i].rad = rad;
    groupArray[i + count].rad = rad + 2 * pi;
    groupArray[i + count].size = groupArray[i].size;
  }

  printArray(groupArray, count * 2);
  mergeSort(groupArray, 0, (count * 2) - 1);
  printArray(groupArray, count * 2);

  /**
   * Check the distance between current group and the next group.
   * If the distance is larger than the angle, return 0.
   * If the distance is less than the angle,
   * Let's say the projection starts 1 angle after the current group.
   * In that case, what is the radian, and what groups are in there?
   * If that radian
   */

  int minPeopleCount = -1;
  double maxDistance = 0;
  for (int i = 0; i < count; i++) {
    if (minPeopleCount == 0) break;
    printf("%lf, %lf\n", groupArray[i + 1].rad, groupArray[i].rad);
    if (groupArray[i + 1].rad - groupArray[i].rad > maxDistance) {
      maxDistance = groupArray[i + 1].rad - groupArray[i].rad;
      printf("max distance: %lf\n", maxDistance);
    }

    printf("Testing group: %d\n", i);
    double tempAngle = groupArray[i].rad + (1 * pi / 180) + angle;
    printf("projection angle is %lf\n", tempAngle);

    int inProjectionCount = 0;
    for (int j = i + 1; j < count * 2; j++) {
      if (groupArray[j].rad <= tempAngle) {
        printf("group %d is in projection (%lf) \n", j, groupArray[j].rad);
        inProjectionCount += groupArray[j].size;
      } else {
        printf("group %d is outside projection, (%lf) \n", j,
               groupArray[j].rad);
        break;
      }
    }
    printf("Total of %d people in projection\n", inProjectionCount);
    if (minPeopleCount < 0 || inProjectionCount < minPeopleCount) {
      minPeopleCount = inProjectionCount;
    }
  }
  printf("minimum people count is %d\n", minPeopleCount);
  printf("max distance count is %.4lf\n", maxDistance * (180 / pi));

  return 0;
}