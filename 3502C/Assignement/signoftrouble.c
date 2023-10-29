#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int maxSignLength = 100000;
  char *oldSign = malloc(sizeof(char) * maxSignLength);
  char *newSign = malloc(sizeof(char) * maxSignLength);

  fgets(oldSign, 100002, stdin);
  fgets(newSign, 100002, stdin);

  int *frequencyArray = calloc(25, sizeof(int));

  // subtract one to ignore \n
  int oldSignLen = strlen(oldSign) - 1;
  for (int i = 0; i < oldSignLen; i++)
    frequencyArray[(oldSign[i] - 'A')] +=
        1;  // subtract by 'A' to shift A as index 0

  int answer = 0;

  // subtract one to ignore \n
  int newSignLen = strlen(newSign) - 1;
  for (int i = 0; i < newSignLen; i++) {
    // ignore checking spaces
    if (newSign[i] == ' ') continue;

    // subtract by 'A' to shift A as index 0
    int targetIndex = newSign[i] - 'A';
    int targetFrequency = frequencyArray[targetIndex];

    if (targetFrequency < 1)  // when oldSign no longer has characters available
      answer += 1;
    else  // take a character from oldSign
      frequencyArray[targetIndex] -= 1;
  }

  printf("%d\n", answer);

  // memory clean up
  free(oldSign);
  free(newSign);
  free(frequencyArray);

  return 0;
}