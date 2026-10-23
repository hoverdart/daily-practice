"use strict";

function shortestRequiredSignalWindow(events, required) {
  if (required.length === 0) return [0, -1];

  const need = new Map();
  for (const x of required) need.set(x, (need.get(x) ?? 0) + 1);

  let missing = required.length;
  let left = 0, bestStart = -1, bestLength = Infinity;

  for (let right = 0; right < events.length; right++) {
    const x = events[right];
    if (need.has(x)) {
      const before = need.get(x);
      if (before > 0) missing--;
      need.set(x, before - 1);
    }

    while (missing === 0) {
      const length = right - left + 1;
      // Strict improvement preserves earliest start among equal lengths.
      if (length < bestLength) {
        bestLength = length;
        bestStart = left;
      }
      const y = events[left++];
      if (need.has(y)) {
        const after = need.get(y) + 1;
        need.set(y, after);
        if (after > 0) missing++;
      }
    }
  }
  return bestStart < 0 ? [-1, -1] : [bestStart, bestStart + bestLength - 1];
}

module.exports = { shortestRequiredSignalWindow };

