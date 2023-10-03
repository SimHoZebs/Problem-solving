/**
A sliding window problem. 
A variable stores the maximum value, while a temp variable continues to add all the numbers.
The initial index resets whenever the current index has a value larger than all the previous temp sum.
Whenever the temp sum is larger than the max sum, that becomes the new max sum.
 */
function maxSubArray(nums: number[]): number {
  let local = 0;
  let global = -Infinity;

  for (const num of nums) {
    local = Math.max(num, local + num);
    if (local > global) global = local;
  }

  return global;
}

//fails at [8,-19,5,-4,20]
function WRONG_SOLUTION(nums: number[]): number {
  let sum = nums[0];
  let lastAdded = true;

  for (let i = 1; i < nums.length; i++) {
    console.log("the sum is now", sum);
    console.log(`checking nums[${i}]: ${nums[i]}`);

    if (nums[i] > 0) {
      if (sum < 0) {
        console.log("starting a new chain");
        sum = nums[i];
      } else if (lastAdded) {
        console.log("adding it to the chain");
        sum += nums[i];
      } else if (nums[i] > sum) {
        console.log("starting a new chain");
        sum = nums[i];
      }
    } else {
      console.log("num is negative, checking its worth");

      //if negative, add all the negative numbers coming after it.
      let negSum = nums[i];

      let j = i + 1;
      for (j; j < nums.length; j++) {
        console.log(`checking num[${j}]: ${nums[j]}`);

        if (nums[j] > 0 || j + 1 === nums.length) {
          console.log("positive number or reached the end. ending negSum");
          i = j - 1;
          break;
        }
        console.log("Adding to negSum");
        negSum += nums[j];
      }

      //if sum of negative numbers make the number 0, then they don't need to be part of the subarray.
      if (sum + negSum < 0) {
        if (negSum > sum) {
          console.log("negsum is larger than sum");

          sum = negSum;
        } else {
          console.log("adding negSum makes sum negative. Skipping");
          lastAdded = false;
        }
      } else {
        console.log(
          "adding negSum keeps sum positive. Checking if posSum makes it worth it"
        );

        //if sum was positive, see if there is a sum of positive numbers that are bigger than the negative sum.
        let posSum = 0;

        for (j; j < nums.length; j++) {
          console.log(`checking num[${j}]: ${nums[j]}`);
          if (nums[j] < 0 || j + 1 == nums.length) {
            console.log("negative number, or reached the end, ending posSum");
            i = j - 1;
            break;
          }
          console.log("Adding to posSum");
          posSum += nums[j];
        }

        //if positive sum is bigger than negSum, then all of them should be part of the subArray.
        if (posSum > -negSum) {
          console.log("posSum is larger. Worth adding negNum");
          lastAdded = true;
          sum += negSum + posSum;
        } else {
          console.log("posSum is smaller, skipping");
          lastAdded = false;
          continue;
        }

        //if positive sum is bigger than the sum by then, then the positive sum is the start of the subarray.
        if (posSum > sum) {
          console.log("posSum is larger than sum. posSum is subArray");
          lastAdded = true;
          sum = posSum;
        }
      }
    }
  }
  return sum;
}
