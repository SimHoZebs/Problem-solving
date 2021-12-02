"use strict";
/**
 * This function will assume there's always a solution.
 */
function twoSum(nums, target) {
    let answer = [];
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
const nums = [5, 2, 3, 9];
const target = 5;
console.log(twoSum(nums, target));
