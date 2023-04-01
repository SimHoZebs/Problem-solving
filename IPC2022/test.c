#include <stdio.h>
void changeIt(int *x, int y)
{

  *x = *x;

  y++;
}

void selectionSort(int *list)
{

  printf("size on n %d\n", sizeof(list) / sizeof(list[0]));
  int n = sizeof(list) / sizeof(list[0]); // len list

  for (int i = 0; i < n; i++)
  {

    int min = i;

    for (int j = i + 1; j < n; j++)
    {

      if (list[j] > list[min])
        min = j;
    }

    if (min != 0)
    {
      int temp = list[min];
      list[min] = list[i];
      list[i] = temp;
    }
  }
}
int main()
{
  int test[5] = {1, 3, 2, 4, 5};
  printf("size %d\n", sizeof(test) / sizeof(test[0]));
  selectionSort(test);
  for (int i = 0; i < 5; i++)
  {

    printf("%d", test[i]);
  }

  return 0;
}
