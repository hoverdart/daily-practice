"use strict";

function shortestArchiveCut(ids, cap) {
  const remaining = new Map();
  for (const id of ids) remaining.set(id, (remaining.get(id) ?? 0) + 1);
  let over = 0;
  for (const count of remaining.values()) if (count > cap) over++;
  if (over === 0) return 0;
  let left = 0, best = ids.length;
  for (let right = 0; right < ids.length; right++) {
    const id = ids[right], before = remaining.get(id);
    remaining.set(id, before - 1);
    if (before === cap + 1) over--;
    while (over === 0) {
      best = Math.min(best, right - left + 1);
      const restored = ids[left++], count = remaining.get(restored);
      remaining.set(restored, count + 1);
      if (count === cap) over++;
    }
  }
  return best;
}

module.exports = { shortestArchiveCut };
