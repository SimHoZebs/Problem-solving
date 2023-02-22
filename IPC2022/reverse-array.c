#include <stdio.h>
#include <stdlib.h>

// 30m
int main(int argc, char const *argv[])
{
  int arrLen;
  scanf("%d", &arrLen);

  int *a = malloc(arrLen * sizeof(int));

  for (int i = 0; i < arrLen; i++)
  {
    scanf("%d", &a[i]);
    printf("scanned %d \n", a[i]);

    int *tempArr = malloc(arrLen * sizeof(int));
    for (int j = i; j >= 0; j--)
    {
      printf("Inserting %d to index %d \n", a[j], i - j);
      tempArr[i - j] = a[j];
    }
    free(a);
    a = tempArr;
  }

  for (int i = 0; i < arrLen; i++)
  {
    printf("%d ", a[i]);
  }

  return 0;
}

// Every time an element is added, a new array should be created and become the reverse version of it.