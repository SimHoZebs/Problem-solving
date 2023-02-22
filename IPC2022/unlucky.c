#include <stdio.h>

// 54m 31s
// The main problem was my brain trying to figure out how the numbers should be shifted to an empty spot.

// Maybe it would've been better if I had list as a pointer to an array that stores the numbers, and once specific numbers were cleared, I create a new shorter array that stores all of the previous array but 0. Once the process is complete, list could point to that new array. The length array also only needs to go through 1000 divided by the interval from then on.

int main(int argc, char const *argv[])
{
  int list[10000];
  int passNum;
  scanf("%d", &passNum);

  // generate positive odd intergers
  for (int i = 0; i < 10000; i++)
  {
    list[i] = (2 * i) + 1;
  }

  printf("last num: %d\n", list[9999]);

  for (int i = 1; i < passNum - 1; i++)
  {
    // select interval and remove those index
    int interval = list[i];
    for (int t = 1; interval * t < 10000; t++)
    {
      // printf("removing %d\n", list[(interval * t) - 1]);
      list[(interval * t) - 1] = 0;
    }

    // rewrite the list removing the removed numbers
    int k = 0;
    for (int j = 0; interval + j + k < 10000; j++)
    {
      // printf("Checking index %d\n", interval + j + k);
      int nextNum = list[interval + j + k];
      while (nextNum == 0)
      {
        k++;
        nextNum = list[interval + j + k];
      }

      // printf("inserting %d in %d\n", list[interval + j + k], interval + j - 1);
      list[interval + j - 1] = nextNum;
    }
  }

  for (int i = 0; i < 100; i++)
  {
    printf("%d ", list[i]);
  }
  printf("\n");

  printf("%d", list[passNum - 1]);
  return 0;
}
