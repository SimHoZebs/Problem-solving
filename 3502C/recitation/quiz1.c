#include <stdio.h>
#include <stdlib.h>

// Q1
int q1(int argc, char const* argv[]) {
  int n;
  scanf_s("%d", &n);
  char* word = calloc(n, sizeof(char));

  return 0;
}

// Q2
//  Pre-condition: list1 is length n, sorted, with unique values.
//  list2 is length m, sorted, with unique values.
//  Post-condition: All elements belonging to both lists are
//  returned in a dynamically allocated array.
int* slmp_linear(int list1[], int n, int list2[], int m, int* news) {
  int* res = malloc(n * sizeof(int));
  int i = 0, j = 0, k = 0;
  while (i < n && j < m) {
    if (list1[i] < list2[j])
      i++;
    else if (list2[j] < list1[i])
      j++;
    else {
      res[k] = list1[i];
      k++;
      i++;
      j++;
    }
  }
  res = realloc(res, sizeof(char) * k);
  *news = k;
  return res;
}
// Q3
int** makeCustomMultTable(int* list1, int len1, int* list2, int len2) {
  int** res = malloc(sizeof(int*) * len1);

  for (int i = 0; i < len2; i++) {
    res[i] = malloc(sizeof(int) * len2);
  }

  for (int i = 0; i < len1; i++) {
    for (int j = 0; j < len2; j++) {
      res[i][j] = list1[i] * list2[j];
    }
  }

  return res;
}

// Q4
int main() {
  int** multtable;
  int len1;
  int len2;

  for (int i = 0; i < len1; i++) {
    free(multtable[i]);
  }
  free(multtable);

  return 0;
}