#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  // from 1 to t;
  unsigned int size;
  scanf("%u", &size);
  size--;

  int listen;
  scanf("%d\n", &listen);

  int *tracks = malloc(sizeof(int) * listen);

  for (int i = 0; i < listen; i++) {
    int val;
    scanf("%d", &val);

    tracks[i] = val - 1;
  }

  unsigned int presses = 0;
  int halfSize = size / 2;

  for (int i = 0; i < listen - 1; i++) {
    int playingNow = tracks[i] + 1;
    if (tracks[i] == size) {
      playingNow = 0;
    }

    int dist = tracks[i + 1] - playingNow;

    if (playingNow == tracks[i + 1]) {
      continue;
    } else if (dist == playingNow - 1 || dist == playingNow + 1) {
      presses++;
    } else if (dist < 0) {
      if (dist < -halfSize) {
        presses += size - tracks[i] + tracks[i + 1];
      } else {
        presses += -dist;
      }
    } else if (dist > 0) {
      if (dist > halfSize + 1) {
        presses += size - tracks[i] + tracks[i + 1];
      } else {
        presses += dist;
      }
    } else {
      continue;
    }
  }

  printf("%u", presses);

  return 0;
}
