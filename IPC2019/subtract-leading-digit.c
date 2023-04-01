//Ho Sim Gold#1
#include <math.h>
#include <stdio.h>

int test(int startNum, int numSize, int endingNum, int seqLen) {
  // based on the size of the number, do / to find the first number
  int firstNum = startNum / pow(10, numSize);
  int newStartNum = startNum - firstNum;
  seqLen += 1;
  if (newStartNum <= endingNum) {
    return seqLen;
  } else {
    int newNumSize = log10(newStartNum);
    return test(newStartNum, newNumSize, endingNum, seqLen);
  }
}

int main() {
  // find the size of the number
  int startNum;
  scanf_s("%d", &startNum);
  int endingNum;
  scanf_s("%d", &endingNum);
  int numSize;
  numSize = log10(startNum);

  int seqLen = 0;
  printf("%d numbers in sequence", test(startNum, numSize, endingNum, seqLen));

  return 0;
}
