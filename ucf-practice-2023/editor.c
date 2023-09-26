#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCOMPLETE SOLUTION

/*
  gcc editor.c -o a && ./a
*/
int main() {
  int lineCount;
  scanf("%d", &lineCount);

  int* charCountArray = malloc(sizeof(int) * lineCount);
  for (int i = 0; i < lineCount; i++) {
    scanf("%d", charCountArray[i]);
  }

  int initPos[2];
  scanf("%d", initPos[0]);
  scanf("%d", initPos[1]);

  int targetPos[2];
  scanf("%d", targetPos[0]);
  scanf("%d", targetPos[1]);

  int currPos[2] = {initPos[0], initPos[1]};

  return 0;
}

int calcDistance(int* currPos, int* targetPos, int* charCountArray) {
  int lineDiff = targetPos[0] - currPos[0];
  int distance = 0;

  if (lineDiff == 0) {
    return targetPos[1] - currPos[0];
  }

  if (lineDiff > 0) {
    distance += charCountArray[currPos[0]] - currPos[1];
    for (int i = 1; i < lineDiff; i++) {
      distance += charCountArray[currPos[0] + i];
    }
    distance += targetPos[1];
  } else {
    distance += currPos[1];

    for (int i = 1; i < lineDiff; i++) {
      distance += charCountArray[currPos[0] + i];
    }
    distance += charCountArray[targetPos[0]] - targetPos[1];
  }

  return distance;
}