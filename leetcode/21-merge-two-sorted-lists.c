#include <stdio.h>

// INCOMPLETE SOLUTION

/**
 * Definition for singly-linked list.
 */

struct ListNode {
  int val;
  struct ListNode *next;
};

void merge(struct ListNode *node, struct ListNode *l1, struct ListNode *l2) {
  if (!(l1) && !(l2)) return;

  if (!l1 && l2) {
    node->next = l2;
    return;
  } else if (!l2 && l1) {
    node->next = l1;
    return;
  }

  struct ListNode *nextL1 = l1->next;
  struct ListNode *nextL2 = l2->next;

  if (l1->val == l2->val) {
    node->next = l1;
    l1->next = l2;
    merge(l2, nextL1, nextL2);
  }
  if (l1->val < l2->val) {
    node->next = l1;
    l1->next = l2;
    merge(l1, nextL1, l2);
  } else {
    node->next = l2;
    l2->next = l1;
    merge(l2, l1, nextL2);
  }
}

// 1,4,5
// 1,2,3
struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2) {
  struct ListNode startNode = {0};

  merge(&startNode, l1, l2);

  return startNode.next;
}

int main() { return 0; }