#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc triangle.c -o a && ./a
*/

int main() {
  int points;
  scanf("%d", &points);

  points *= 3;

  int** coords = malloc(sizeof(int*) * points);

  for (int i = 0; i < points; i++) {
    coords[i] = calloc(2, sizeof(int));
    scanf("%d", &coords[i][0]);
    scanf("%d", &coords[i][1]);
  }

  float smallA = 100000;
  float largeA = 0;

  int k = 0;
  while (1) {
    int i = (3 * k) - 1;
    if (i < 0) {
      i = 0;
    }
    printf("i: %d", i);
    if (i >= points - 1) {
      break;
    }

    float area =
        (1.0 / 2.0) * (coords[i][0] * (coords[i + 1][1] - coords[i + 2][1]) +
                       coords[i + 1][0] * (coords[i + 2][1] - coords[i][1]) +
                       coords[i + 2][0] * (coords[i][1] - coords[i + 1][1]));

    if (area < 0) {
      area = -1.0 * area;
    }

    printf("area: %lf\n", area);

    if (area < smallA) {
      smallA = area;
    }
    if (area > largeA) {
      largeA = area;
    }
    k++;
  }

  printf("diff: %lf", largeA - smallA);

  return 0;
}