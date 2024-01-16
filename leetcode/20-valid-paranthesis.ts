/**
 * Got slightly confused by the vague question. It didn't specify whether ([)] is valid or not.
 */
function isValid(s: string): boolean {
  const map: { [key: string]: number; } = { '(': 0, ')': 0, '{': 1, '}': 1, '[': 2, ']': 2 };
  const stack = [];

  for (let i = 0; i < s.length; i++) {
    const index = map[s[i]];

    switch (s[i]) {
      case '(':
      case '{':
      case '[':
        stack.push(index);
        break;

      default:
        const popped = stack.pop();
        if (popped !== index) return false;
        break;
    }
  }

  return !stack.length;
};
