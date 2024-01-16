/**
 * This function will assume there's always a solution.
 * O(n^2)
 * Dec 3, 2021 
 */
function twoSum(nums: number[], target: number): number[] {
  let answer: number[] = [];

  for (let i = 0; i < nums.length - 1; i++) {
    const complement = target - nums[i];

    for (let j = i + 1; j < nums.length; j++) {
      if (nums[j] === complement) {
        answer = [i, j];
      }
    }
  }

  return answer;
}

const nums = [2, 3, 4, 5, 7, 9, 10, 20, 50];
const target = 8;

console.log(twoSum(nums, target));

/**
 * Second attempt 
 * O(n) + O(nlogn) + O(n) = O(nlogn)
 * JAN 16, 2024
 */
function twoSum2(nums: number[], target: number): number[] {
  const test = nums.map((num, i) => [i, num]);

  test.sort((a, b) => a[1] - b[1]);
  let low = 0;
  let high = nums.length - 1;

  while (true) {
    const res = test[low][1] + test[high][1];
    if (res > target) {
      high--;
    } else if (res < target) {
      low++;
    } else {
      return [test[low][0], test[high][0]];
    }
  }
};