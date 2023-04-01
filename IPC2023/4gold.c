//Ho Sim Gold #4
#include <math.h>
#include <stdio.h>

int main(){
  int input;
  scanf_s("%d", &input);
  long long squared = pow(input,2);

  int size = log10l(squared);
  size += log10l(squared/pow(10,size-1));

  int firsthalf = size/2;
  int part1 = squared / pow(10, size- firsthalf);
  int part2 = squared % (int)pow(10, firsthalf);

  if(part1+part2 == input){
    printf("Splitable");
  }else{
    printf("Not Splitable");
  }
  
  return 0;
}
