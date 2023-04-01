//Ho Sim Gold#3
#include <math.h>
#include <stdio.h>

int main() {
  int num;
  scanf_s("%d", &num);
  int size = log10(num);
  printf("size %d\n", size);

  int ans = 0;
  for (int i = 0; i <= size; i++) {
    int numInPos;
    numInPos = num / pow(10, size - i);
    numInPos = numInPos % 10;

    int weightNumInPos = numInPos * (i + 1);
    ans += weightNumInPos;
  }
  printf("weighted sum is %d", ans);
  return 0;
}
