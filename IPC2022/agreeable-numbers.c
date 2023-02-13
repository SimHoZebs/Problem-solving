#include <stdio.h>

#define LEN 99

// These questions are solved for speed; They can definitely be optimized.

int main(int argc, char const *argv[])
{
  int x, y;
  // sum of the divisors of x == Y
  // sum of the divisors of y == x
  // divisor is num other than itself.

  int divX[LEN];
  int divY[LEN];

  scanf("%d %d", &x, &y);

  int divNumX;
  int divCountX = 0;
  for (divNumX = 2; divNumX <= x / 2; divNumX++)
  {
    // find divisors
    if (x % divNumX == 0)
    {
      divX[divCountX] = divNumX;
      divCountX++;
    }
  }

  int divNumY;
  int divCountY = 0;
  for (divNumY = 2; divNumY <= y / 2; divNumY++)
  {
    // find divisors
    if (y % divNumY == 0)
    {
      divY[divCountY] = divNumY;
      divCountY++;
    }
  }

  int divSumX = 1;
  for (int i = 0; i < divCountX; i++)
  {
    divSumX += divX[i];
  }

  int divSumY = 1;
  for (int i = 0; i < divCountY; i++)
  {
    divSumY += divY[i];
  }

  printf("%sgreeable numbers", divSumX == y && x == divSumY ? "A" : "Not a");

  return 0;
}
