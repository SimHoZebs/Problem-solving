// Definition for a binary tree node.
class TreeNode {
  val: number;
  left: TreeNode | null;
  right: TreeNode | null;
  constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
    this.val = val === undefined ? 0 : val;
    this.left = left === undefined ? null : left;
    this.right = right === undefined ? null : right;
  }
}

// Initial solution
function old(root: TreeNode | null): TreeNode | null {
  if (!root) return null;

  let leftClone = null;

  if (root.left)
    leftClone = new TreeNode(root.left.val, root.left.left, root.left.right);

  let rightClone = null;

  if (root.right)
    rightClone = new TreeNode(
      root.right.val,
      root.right.left,
      root.right.right
    );

  root.left = invertTree(rightClone);
  root.right = invertTree(leftClone);

  return root;
}

function invertTree(root: TreeNode | null): TreeNode | null {
  if (!root) return null;
  const l = root.left;
  root.left = invertTree(root.right);
  root.right = invertTree(l);
  return root;
}
