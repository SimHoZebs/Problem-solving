"use strict";
/**
 * Definition for singly-linked list.
 */
class ListNode {
    val;
    next;
    constructor(val, next) {
        this.val = (val === undefined ? 0 : val);
        this.next = (next === undefined ? null : next);
    }
}
const newListNode = new ListNode(0);
function addTwoNumbers(l1, l2, carry = 0) {
    const sum = l1.val + l2.val + carry;
    const result = new ListNode(sum % 10);
    const nextCarry = Math.floor(sum / 10);
    if (nextCarry || l1.next || l2.next) {
        result.next = addTwoNumbers(l1.next ? l1.next : newListNode, l2.next ? l2.next : newListNode, nextCarry);
    }
    return result;
}
;
// function addTwoNumbers(l1: ListNode, l2: ListNode): ListNode | null {
//   const result = new ListNode(0);
//   let carry = 0;
//   let node1: ListNode | null = l1;
//   let node2: ListNode | null = l2;
//   while (node1 || node2 || carry) {
//     let val1 = node1 ? node1.val : 0;
//     let val2 = node2 ? node2.val : 0;
//     const newNode = new ListNode(val1 + val2 + carry);
//     if (newNode.val > 9) {
//       carry = 1;
//       newNode.val -= 10;
//     }
//     else {
//       carry = 0;
//     }
// node1 = l1.next;
// node2 = l2.next;
//   }
// return result;
// }
const arr1 = [9, 9, 9, 9, 9, 9, 9];
const arr2 = [9, 9, 9, 9];
function makeListNode(arr, index = 0) {
    if (index === arr.length - 1) {
        return new ListNode(arr[index]);
    }
    const node = new ListNode(arr[index], makeListNode(arr, index + 1));
    return node;
}
const l1 = makeListNode(arr1);
const l2 = makeListNode(arr2);
console.log(JSON.stringify(addTwoNumbers(l1, l2), null, 2));
