#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a stack.c -lm && ./a
type ./input.md | ./a.exe > ./output.md
*/

// Q1
int zeros(int n) {
  int res = 0;
  while (n != 0) {
    res += zeros(n / 5);
  }
  return res;
}

// Q2
int sumEven(int vals[], int low, int high) {
  int sum = 0;

  while (vals[low] % 2 != 0) sum += vals[low];

  if (low >= high) return sum;

  sum += sumEven(vals, low + 1, high);
}

// Q3
int minMovesToWin(int n) {
  int moves = 0;

  if (n <= 0) return moves;

  moves++;
  moves += minMovesToWin(n > 10 ? n / 3 : n - 10);
}

// Q4
int f(int n);

int fcomp(int n, int k) {
  int answer = f(n);
  if (k > 1) {
    answer = fcomp(answer, k - 1);
  } else {
    answer = f(n);
    return answer;
  }
};

// Q5
int search(int numbers[], int low, int high, int value) {
  int i = (high + low) / 2;

  if (low >= high) return -1;
  if (numbers[i] == value) return i;

  if (numbers[i] > value) {
    i = search(numbers, low, i - 1, value);
  } else {
    i = search(numbers, i + 1, high, value);
  }
}