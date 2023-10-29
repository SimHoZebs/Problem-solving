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