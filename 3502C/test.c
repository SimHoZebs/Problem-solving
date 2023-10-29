#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a test.c -lm && ./a
./a < ./input.md > ./output.md
*/
int compute(int array[], int low, int high) {
  if (low == high) return array[low] % 3 + 1;
  int mid = (low + high) / 2;
  printf("low:%d, mid: %d\n", low, mid);
  int left = compute(array, low, mid);
  printf("left: %d\n", left);
  printf("mid+1:%d, high: %d\n", mid + 1, high);
  int right = compute(array, mid + 1, high);
  printf("right: %d\n", right);
  return left * right;
}

int main() {
  int array[7] = {17, 4, 19, 30, 47, 999, 13};
  int result = compute(array, 4, 6);
  printf("%d\n", result);
  return 0;
}