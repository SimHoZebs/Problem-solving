#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 999

int re(char num[SIZE], int i)
{

  if (num[i + 1] <= '9' && num[i + 1] >= '0')
  {
    // printf("|%c - %c| = %d\n", num[i], num[i + 1], abs(num[i] - num[i + 1]));
    num[i] = '0' + abs(num[i] - num[i + 1]);
    re(num, i + 1);
  }
  else
  {
    if (i == 0)
    {
      printf("%s", num);
    }
    else
    {
      num[i] = ' ';
      // printf("Current number is %s\n", num);
      re(num, 0);
    }
  }
}

int main(int argc, char const *argv[])
{

  char num[SIZE];
  scanf("%s", num);
  int numLen = strlen(num);

  re(num, 0);
  return 0;
}
