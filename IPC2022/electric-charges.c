#include <stdio.h>
#include <stdbool.h>

int main()
{
  int kwh;
  const double firstThousandCost = 0.07633;
  const double afterThousandCost = 0.09259;

  printf("Enter the KW hours used: ");
  scanf_s("%d", &kwh);

  int extra = 0;
  double ans = 0;

  if (kwh > 1000)
  {
    extra = kwh - 1000;
    ans = 1000 * firstThousandCost + extra * afterThousandCost;
  }
  else
  {
    ans += kwh * firstThousandCost;
  }

  printf("Amount owed is $%.3lf", ans);
  return 0;
};
