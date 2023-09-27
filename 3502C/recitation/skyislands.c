/**
 * Ho Sim
 * skyislands.c
 * 27 SEP 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a skyislands.c -lm && ./a
./a < ./input.md > ./output.md
*/

int travel(int* visited, int** grid, int islandNum, int islandCount) {
  visited[islandNum] = 1;

  // check if each island has been visited.
  for (int i = 0; i < islandCount; i++) {
    // if all islands have been visited
    if (visited[i] && i + 1 == islandCount) return 1;

    // skip self, visited islands (that isn't the last island), or disconnected
    // islands
    if (islandNum == i || visited[i] || !grid[islandNum][i]) continue;

    // isn't self, is unvisited, and is connected
    return travel(visited, grid, i, islandCount);
  }

  // This part is reached when all islands have been checked but they were
  // visited or disconnected. Therefore false.
  return 0;
}

int main() {
  int islandCount, bridgeCount;

  scanf("%d %d", &islandCount, &bridgeCount);

  // init islands
  int** grid = calloc(islandCount, sizeof(int*));
  for (int i = 0; i < islandCount; i++) {
    grid[i] = calloc(islandCount, sizeof(int));
    grid[i][i] = 1;
  }

  // connecting bridges
  for (int i = 0; i < bridgeCount; i++) {
    int i1, i2;

    scanf("%d %d", &i1, &i2);

    grid[i1 - 1][i2 - 1] = 1;
    grid[i2 - 1][i1 - 1] = 1;
  }

  // array to store truth values for visited islands
  int* visited = malloc(islandCount * sizeof(int));
  int isConnected = travel(visited, grid, 0, islandCount);

  printf("%s\n", isConnected ? "YES" : "NO");

  for (int i = 0; i < islandCount; i++) {
    free(grid[i]);
  }

  free(grid);

  return 0;
}