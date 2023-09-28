#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc -g -O2 -std=c11 -o a 125-valid-palindrome.c -lm && ./a
./a < ./input.md > ./output.md
*/
bool isPalindrome(char* s) {
  int len = strlen(s);

  int l = 0;
  int r = len - 1;
  while (l <= r) {
    char leftLower = tolower(s[l]);
    char rightLower = tolower(s[r]);

    if (!(leftLower >= '0' && leftLower <= '9' ||
          leftLower >= 'a' && leftLower <= 'z')) {
      l++;
      continue;
    }

    if (!(rightLower >= '0' && rightLower <= '9' ||
          rightLower >= 'a' && rightLower <= 'z')) {
      r--;
      continue;
    }

    if (leftLower != rightLower) return false;
    r--;
    l++;
  }

  return true;
}

int main() {
  bool test = isPalindrome("0P");
  printf("%s\n", test ? "true" : "false");

  return 0;
}