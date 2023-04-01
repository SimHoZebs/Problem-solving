#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1h
//  brute force sort, could use better sort
void initSort(int count, char **stringArr)
{
  for (int i = 0; i < count - 1; i++)
  {
    int changed = 1;
    while (changed == 1)
    {
      changed = 0;

      char *str1 = stringArr[i];
      int len1 = strlen(str1);
      for (int j = i + 1; j < count; j++)
      {
        char *str2 = stringArr[j];
        int len2 = strlen(str2);

        printf("comparing st1: %s, str2: %s \n", str1, str2);
        if (len1 < len2)
        {
          char *tempStr = malloc(len2 * sizeof(char));
          strcpy(tempStr, str2);
          strcpy(str2, str1);
          strcpy(str1, tempStr);
          changed = 1;
          printf("After swap st1: %s, str2: %s\n", str1, str2);
        }
        else
        {
          printf("not swapping \n");
        }
      }
    }
  }
}

// Impl after learning the concept
char **quickSort(int count, char **stringArr)
{
  int midIndex = (count - 1) / 2;
  // copy the array
  char **arrCopy = malloc(count * sizeof(char *));
  for (int i = 0; i < count; i++)
  {
    int stringLen = strlen(stringArr[i]);
    arrCopy[i] = malloc((stringLen + 1) * sizeof(char));
    strcpy(arrCopy[i], stringArr[i]);
  }

  if (count == 1)
  {
    return arrCopy;
  }

  // sort first, mid, last items
  // choose pivot in the mid
  char *pivot = arrCopy[midIndex];
  // swap pivot with the last item
  char *temp = malloc(strlen(arrCopy[count - 1]) * sizeof(char));
  strcpy(temp, arrCopy[count - 1]);

  realloc(arrCopy[count - 1], strlen(pivot) * sizeof(char));

  strcpy(arrCopy[count - 1], pivot);

  realloc(arrCopy[midIndex], (strlen(arrCopy[count - 1]) + 1) * sizeof(char));
  strcpy(arrCopy[midIndex], temp);

  // path from left to find item larger than the pivot
  // path from right to find item smaller than the pivot
  // once each are found, swap the two
  // repeat the process until index for item from left is bigger than item from right
  // swap item from left with pivot
  // recursively repeat the process with the left array and right array until there is one item in the array
}

int main(int argc, char const *argv[])
{
  int count;
  printf("Enter count of words: ");
  scanf("%d", &count);
  char **stringArr = malloc(count * sizeof(char *));

  for (int i = 0; i < count; i++)
  {
    char string[99];
    printf("Enter next word: ");
    scanf("%s", string);
    int len = strlen(string);
    stringArr[i] = malloc((len + 1) * sizeof(char));
    strcpy(stringArr[i], string);
  }

  initSort(count, stringArr);
  // quicksort(count, stringArr);

  for (int i = 0; i < count; i++)
  {
    printf("%s ", stringArr[i]);
  }

  return 0;
}
