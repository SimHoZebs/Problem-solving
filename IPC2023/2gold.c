//Ho Sim Gold#2
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int re(int input, int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int firstNum = (int)(input / pow(10, size - i)) % 10;
    int nextNum = (int)(input / pow(10, size - (i + 1))) % 10;

    result += abs(firstNum - nextNum) * pow(10, size - i - 1);
  }

  if (result > 10) {
    int newSize = log10(result);
    return re(result, newSize);
  }
  return result;
}

int main() {
  int input;
  scanf_s("%d", &input);
  int size = log10(input);
  printf("%d", re(input, size));

  return 0;
}
