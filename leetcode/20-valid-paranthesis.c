#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* s) {
  char stack[10000] = {'0'};
  int stackIndex = -1;

  int i = 0;
  while (1) {
    if (s[i] == '\0') {
      if (stackIndex == -1) return true;

      return false;
    }

    switch (s[i]) {
      case '(':
        stackIndex++;
        stack[stackIndex] = ')';
        break;
      case '[':
        stackIndex++;
        stack[stackIndex] = ']';
        break;
      case '{':
        stackIndex++;
        stack[stackIndex] = '}';
        break;
      case ')':
      case '}':
      case ']':
        if (stackIndex == -1 || s[i] != stack[stackIndex]) return false;

        stack[stackIndex] = '0';
        stackIndex--;
        break;
      default:
        break;
    }

    i++;
  }
}

int main() {
  char input[20] = "]";

  bool answer = isValid(input);

  if (answer)
    printf("true");
  else
    printf("false");

  return 0;
}
