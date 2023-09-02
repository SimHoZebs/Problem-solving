#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  gcc -g -O2 -std=c11 -o a portman.c -lm && ./a
*/

int main() {
  char *word1 = malloc(sizeof(char) * 22);
  char *word2 = malloc(sizeof(char) * 22);

  fgets(word1, 22, stdin);
  fgets(word2, 22, stdin);

  char *v1 = calloc(22, sizeof(char));
  int word1Len = strlen(word1) - 1;
  v1[0] = word1[0];
  int v1HasVowel = 0;

  for (int i = 1; i < word1Len; i++) {
    v1[i] = word1[i];

    if (word1[i] == 'a' || word1[i] == 'e' || word1[i] == 'i' ||
        word1[i] == 'o' || word1[i] == 'u') {
      v1HasVowel = 1;
      break;
    }
  }

  int word2Len = strlen(word2) - 1;
  char *v2 = calloc(22, sizeof(char));
  v2[0] = word2[word2Len - 1];
  int v2HasVowel = 0;

  for (int i = word2Len - 2; i >= 0; i--) {
    v2[word2Len - i - 1] = word2[i];
    if (word2[i] == 'a' || word2[i] == 'e' || word2[i] == 'i' ||
        word2[i] == 'o' || word2[i] == 'u') {
      v2HasVowel = 1;
      break;
    }
  }

  int v1Len = strlen(v1);
  int v2Len = strlen(v2);

  char *answer = calloc(42, sizeof(char));

  strcpy(answer, v1);
  if (v2HasVowel) {
    int k = -1;
    for (int i = v2Len - 1; i >= 0; i--) {
      answer[v1Len + k] = v2[i];
      k++;
    }
  } else if (v1HasVowel) {
    int k = 0;
    for (int i = v2Len - 1; i >= 0; i--) {
      answer[v1Len + k] = v2[i];
      k++;
    }
  } else {
    answer[v1Len] = 'o';
    int k = 1;
    for (int i = v2Len - 1; i >= 0; i--) {
      answer[v1Len + k] = v2[i];
      k++;
    }
  }

  printf("%s", answer);

  return 0;
}