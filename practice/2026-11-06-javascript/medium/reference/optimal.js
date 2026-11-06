"use strict";

function countWindowsWithExactCollisions(ids, k) {
  function atMost(limit) {
    if (limit < 0) return 0;
    let left = 0, pairs = 0, total = 0;
    const freq = new Map();
    for (let right = 0; right < ids.length; right++) {
      const x = ids[right], previous = freq.get(x) ?? 0;
      pairs += previous;
      freq.set(x, previous + 1);
      while (pairs > limit) {
        const y = ids[left++], oldCount = freq.get(y);
        pairs -= oldCount - 1;
        if (oldCount === 1) freq.delete(y);
        else freq.set(y, oldCount - 1);
      }
      total += right - left + 1;
    }
    return total;
  }
  return atMost(k) - atMost(k - 1);
}

module.exports = { countWindowsWithExactCollisions };
