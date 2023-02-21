#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// brute force sort, could use better sort

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
        if (len1 > len2)
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

  for (int i = 0; i < count; i++)
  {
    printf("%s ", stringArr[i]);
  }

  return 0;
}
