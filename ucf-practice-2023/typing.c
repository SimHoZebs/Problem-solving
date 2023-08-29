#include <stdio.h>
#include <string.h>

int sameLength(char *w1, char *w2) {
  int w1Len = 0;
  int w2Len = 0;

  for (int i = 0; 1; i++) {
    if (w1[i] == '\0') {
      break;
    }
    w1Len++;
  }

  for (int i = 0; 1; i++) {
    if (w2[i] == '\0') {
      break;
    }
    w2Len++;
  }

  if (w1Len == w2Len) {
    return 1;
  } else {
    return 0;
  }
}

int neighbours(char *w1, char *w2) {
  for (int i = 0; 1; i++) {
    char w1Char = w1[i];
    char w2Char = w2[i];
    if (w1Char == '\0') return 1;

    if (w1Char == w2Char || w1Char + 9 == w2Char || w1Char + 1 == w2Char ||
        w1Char - 1 == w2Char || w1Char - 9 == w2Char || w1Char + 10 == w2Char ||
        w1Char - 8 == w2Char || w1Char + 8 == w2Char || w1Char - 10 == w2Char) {
      continue;
    } else {
      return 0;
    }
  }
}

int main(int argc, char const *argv[]) {
  char w1[22];
  char w2[22];

  char test;
  scanf("%s", w1);
  scanf("%s", w2);

  if (!strcmp(w1, w2)) {
    printf("1");
  } else if (sameLength(w1, w2) && neighbours(w1, w2)) {
    printf("2");
  } else {
    printf("3");
  }

  /* code */
  return 0;
}
