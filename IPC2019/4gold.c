#include <stdio.h>
#include <string.h>

int main() {
  char str1[100];
  scanf_s("%s", str1);
  int str1l = strlen(str1);

  char str2[100];
  scanf_s("%s", str2);
  int str2l = strlen(str2);

  if (str1l != str2l) {
    printf("not equivalent");
    return 0;
  }

  // characters are going to index through an array as their ASCII value
  // If there is a value there already, then use that value.
  int dict[150] = {0};
  for (int i = 0; i < str1l; i++) {
    // see if the first string char has a value in the dictionary
    int dictVal = dict[str1[i]];
    printf("%d\n", dictVal);

    // if the dictionary already has it and it isn't the current char, then it's
    
    // not equivalent.
  }

  return 0;
}
