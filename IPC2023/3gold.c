//Ho Sim Gold#3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int valAtIndex(long long num, int index) {
  int size = log10l(num);
  int test = num/pow(10, size-1);
  size += log10(test);
  if (size == index +1){
   return num % 10;
  }

  return (int)(num / pow(10, size - index -1)) % 10;
}

int main() {
  long long input;
  scanf_s("%lld", &input);

  int size = log10l(input);
  int test = input/pow(10, size-1);
  size += log10(test);

  int ans = 0;
  for (int i = 0; i < size; i++) {
    int curr = valAtIndex(input, i);

    if (i % 2 == 0) {
      ans += curr;
    } else {
      curr = curr * 2;
      int addition = curr >= 10? valAtIndex(curr,0)+valAtIndex(curr,1):curr;
      ans+= addition;
    }
  }
  ans = 10 - (ans % 10);

  printf("%d", ans);
  return 0;
}
