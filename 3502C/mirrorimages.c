/**
 * Ho Sim
 * mirrorimages.c
 * 12 SEP 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc mirrorimages.c -o a && ./a
*/

int main() {
  // number of test cases
  int testNum;
  scanf("%d", &testNum);

  for (int i = 0; i < testNum; i++) {
    int row, col;
    scanf("%d %d", &row, &col);

    char **image = calloc(row, sizeof(char *));

    // scanning image
    for (int j = 0; j < row; j++) {
      image[j] = calloc(col, sizeof(char));
      scanf("%s", image[j]);
    }

    printf("Test %d\n", i + 1);

    // reverse loop
    for (int j = row - 1; j >= 0; j--) {
      for (int k = col - 1; k >= 0; k--) {
        // printing individual characters in reverse
        printf("%c", image[j][k]);
      }

      printf("\n");

      // image section no longer needed
      free(image[j]);
    }

    // original image no longer needed
    free(image);
  }

  return 0;
}