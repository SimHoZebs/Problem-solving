#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCOMPLETE SOLUTION

/*
  gcc 121-stock.c -o a && ./a
*/

int maxProfit(int* prices, int pricesSize) {
  int buy = 0;
  int buyIndex = 0;
  int sell = 0;

  for (int i = 0; i < pricesSize; i++) {
    int tmpBuy = prices[i];
    int tmpSell = 0;

    for (int j = i + 1; j < pricesSize; j++) {
      if (prices[j] > tmpSell) {
        tmpSell = prices[j];
      } else {
        continue;
      }
    }

    if (tmpSell - tmpBuy > sell - buy) {
      sell = tmpSell;
      buy = tmpBuy;
    }
  }

  return sell - buy;
}

int main() { return 0; }