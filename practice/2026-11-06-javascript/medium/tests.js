"use strict";
const assert = require("node:assert/strict");
const { countWindowsWithExactCollisions } = require("./solution");

// Independent O(n^2) oracle; examines each contiguous interval.
function oracle(a, k) {
  let answer = 0;
  for (let l = 0; l < a.length; l++) {
    let pairs = 0;
    const counts = new Map();
    for (let r = l; r < a.length; r++) {
      const old = counts.get(a[r]) || 0;
      pairs += old;
      counts.set(a[r], old + 1);
      if (pairs === k) answer++;
    }
  }
  return answer;
}

const fixed = [
  [[], 0, 0], [[], 10, 0],
  [[7], 0, 1], [[7], 1, 0],
  [[2, 2, 3, 2], 1, 3], [[2, 2, 3, 2], 3, 1],
  [[5, 5, 5], 1, 2], [[5, 5, 5], 3, 1], [[5, 5, 5], 2, 0],
  [[1, 2, 3], 0, 6], [[1, 2, 3], 1, 0],
  [[-1, -1, -1, -1], 6, 1],
  [[0, -1, 0, -1], 1, 2]
];
for (const [a, k, expected] of fixed) {
  const old = a.slice();
  assert.equal(countWindowsWithExactCollisions(a, k), expected, JSON.stringify({a, k}));
  assert.deepEqual(a, old, "mutated input");
}

let seed = 611061;
function rand(n) { seed = (Math.imul(seed, 1664525) + 1013904223) >>> 0; return seed % n; }
for (let t = 0; t < 1600; t++) {
  const a = Array.from({ length: rand(34) }, () => rand(9) - 4);
  const k = rand(45);
  assert.equal(countWindowsWithExactCollisions(a, k), oracle(a, k), JSON.stringify({a, k}));
}
const n = 120000;
const unique = Array.from({ length: n }, (_, i) => i);
const same = Array(n).fill(-8);
assert.equal(countWindowsWithExactCollisions(unique, 0), n * (n + 1) / 2);
assert.equal(countWindowsWithExactCollisions(unique, 1), 0);
assert.equal(countWindowsWithExactCollisions(same, 0), n);
assert.equal(countWindowsWithExactCollisions(same, 1), n - 1);
assert.equal(countWindowsWithExactCollisions(same, 3), n - 2);
assert.equal(countWindowsWithExactCollisions(same, 2), 0);
console.log("PASS medium: fixed, 1600 seeded O(n^2)-oracle cases, 120k stress");
