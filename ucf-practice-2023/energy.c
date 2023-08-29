#include <stdio.h>

int main(int argc, char const *argv[]) {
  int first;
  scanf("%d", &first);
  int additional;
  scanf("%d", &additional);

  int consumption;
  scanf("%d", &consumption);

  int total;

  if (consumption <= 1000) {
    total = consumption * first;
  } else {
    total = 1000 * first + (consumption - 1000) * additional;
  }

  printf("%d", total);

  return 0;
}
