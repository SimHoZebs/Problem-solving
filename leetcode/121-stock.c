#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCOMPLETE SOLUTION

/*
  gcc 121-stock.c -o a && ./a
*/

int slowMaxProfit(int* prices, int pricesSize) {
  int buy = 0;
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

//[7,1,5,3,6,4]
//[7,4,5,10,1,3,2]
//[11,7,2,4,1,2]
int maxProfit(int* prices, int pricesSize) {
  int sellIndex = 1, buyIndex = 0, profit = 0;

  while (sellIndex < pricesSize) {
    if (prices[sellIndex] < prices[buyIndex]) {
      buyIndex = sellIndex;
    } else if (prices[sellIndex] - prices[buyIndex] > profit) {
      profit = prices[sellIndex] - prices[buyIndex];
    }
    sellIndex++;
  }

  return profit;
}

int main() { return 0; }