"use strict";
function firstNearbyDuplicate(ids, k) {
  const window = new Set();
  for (let right = 0; right < ids.length; right++) {
    if (right > k) window.delete(ids[right - k - 1]);
    if (window.has(ids[right])) return right;
    window.add(ids[right]);
  }
  return -1;
}
module.exports = { firstNearbyDuplicate };
