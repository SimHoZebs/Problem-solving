//Ho Sim Gold#5
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
  char string[100];

  fgets(string, 100, stdin);

  int len = strlen(string);
  for (int i = 0; i < 170; i++) {
    if (!isalpha((char)i)) continue;
    int charPosArray[100] ={0};
    int charCount = 0;

    for (int j = 0; j < len; j++) {
      if (tolower(string[j]) == (char)i) {
        charPosArray[charCount] = j;
        charCount++;
      }else{
      }
    }

    if (charCount > 0) {
      printf("%c:", i);
      for (int i = 0; i < charCount; i++) {
        printf(" %d", charPosArray[i] +1);
      } printf("\n");
    }
  }

  return 0;
}
