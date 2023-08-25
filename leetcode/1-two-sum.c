#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
  *returnSize = 2;
  int *answer = malloc(sizeof(int) * 2);

  for (int i = 0; i < numsSize; i++)
  {
    // always smaller than target
    int firstNum = nums[i];
    printf("firstNum %d\n", firstNum);

    for (int j = i + 1; j < numsSize; j++)
    {
      if (nums[j] + firstNum == target)
      {
        answer[0] = i;
        answer[1] = j;
        return answer;
      }
    }
  }

  return answer;
}

int main()
{
  int nums[4] = {3, 2, 4};
  int numsSize = 3;
  int target = 6;
  int returnSize;

  int *answer = twoSum(nums, numsSize, target, &returnSize);
  for (int i = 0; i < returnSize; i++)
  {
    printf("answer: %d\n", answer[i]);
  }

  return 0;
}
