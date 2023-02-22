#include <stdio.h>

// probs could be more optimized - 19m 02s
int main(int argc, char const *argv[])
{

  // the starting number can not be bigger than half of the input.
  int target;
  printf("Enter weight:");
  scanf("%d", &target);
  int largestNum = target / 2;

  // Loop from largestNum and keep adding num, if num goes over the input, then combination doesn't work. Go down until we use one.

  int sumOfFirst = 0;
  int numOfComb = 0;

  for (int starterNum = largestNum; starterNum > 0; starterNum--)
  {
    int sum = starterNum;
    printf("starting with %d\n", sum);
    for (int nextNum = starterNum + 1; sum <= target; nextNum++)
    {
      sum += nextNum;
      if (sum == target)
      {
        printf("combination starting with %d\n", starterNum);
        numOfComb += 1;
        sumOfFirst += starterNum;
        break;
      }
      else if (sum > target)
      {
        // printf("no combination starting with %d\n", starterNum);
        break;
      }
    }
  }

  printf("%d %d", numOfComb, sumOfFirst);
  return 0;
}
