/**
 * This function will assume there's always a solution.
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
