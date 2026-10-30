"use strict";

/**
 * @param {number[]} codes
 * @param {number} k
 * @returns {number} longest contiguous segment made constant with <= k edits
 */
function longestRecalibratableRun(codes, k) {
  // TODO: two pointers + Map<code, count>.
  // maxFreq can remain the maximum frequency EVER observed during expansion.
  // Shrink while (right - left + 1 - maxFreq) > k.
  throw new Error("TODO: implement longestRecalibratableRun");
}

module.exports = { longestRecalibratableRun };
