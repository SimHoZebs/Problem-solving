#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
  char s1[3];
  char s2[3];
  int s1Len;
  int s2Len;

  char s3[3];
  int s3Len;

  printf("Enter first segment: ");
  scanf("%s", s1);
  printf("Enter first length: ");
  scanf("%d", &s1Len);
  printf("Enter second segment: ");
  scanf("%s", s2);
  printf("Enter second length: ");
  scanf("%d", &s2Len);

  if (strcmp(s1, "AC") == 0)
  {
    // then s2 is a side.
    s3Len = sqrt(pow(s1Len, 2) - pow(s2Len, 2));
    strcpy(s3, strcmp(s2, "BC") == 0 ? "AB" : "BC");
  }
  else if (strcmp(s2, "AC") == 0)
  {
    s3Len = sqrt(pow(s2Len, 2) - pow(s1Len, 2));
    strcpy(s3, strcmp(s1, "BC") == 0 ? "AB" : "BC");
  }
  else
  {
    s3Len = sqrt(pow(s1Len, 2) + pow(s2Len, 2));
    strcpy(s3, "AC");
  }

  printf("%s %d", s3, s3Len);

  return 0;
}