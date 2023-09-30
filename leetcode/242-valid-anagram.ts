function isAnagram(s: string, t: string): boolean {
  const charArray = Array(26).fill(0);

  if (t.length !== s.length) return false;

  for (let i = 0; i < s.length; i++) {
    const index = s[i].charCodeAt(0) - "a".charCodeAt(0);

    charArray[index]++;
  }

  for (let i = 0; i < t.length; i++) {
    const index = t[i].charCodeAt(0) - "a".charCodeAt(0);

    if (charArray[index] < 1) return false;

    charArray[index]--;
  }

  return true;
}

console.log(isAnagram("car", "rat"));
