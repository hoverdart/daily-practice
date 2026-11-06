"use strict";
const assert = require("node:assert/strict");
const { closestBlockingBeacon } = require("./solution");

function oracle(a) {
  return a.map((x, i) => {
    for (let j = i - 1; j >= 0; j--) if (a[j] >= x) return j;
    return -1;
  });
}

const fixed = [
  [[], []],
  [[42], [-1]],
  [[6, 2, 2, 7, 3, 8], [-1, 0, 1, -1, 3, -1]],
  [[5, 5, 5, 5], [-1, 0, 1, 2]],
  [[1, 2, 3, 4], [-1, -1, -1, -1]],
  [[4, 3, 2, 1], [-1, 0, 1, 2]],
  [[-5, -9, -7, -7, 0], [-1, 0, 0, 2, -1]],
  [[1000000000, -1000000000, 1000000000], [-1, 0, 0]]
];
for (const [a, expected] of fixed) {
  const snapshot = a.slice();
  assert.deepEqual(closestBlockingBeacon(a), expected, JSON.stringify(a));
  assert.deepEqual(a, snapshot, "input was modified");
}

let seed = 20261106;
function rand(n) { seed = (Math.imul(seed, 1664525) + 1013904223) >>> 0; return seed % n; }
for (let t = 0; t < 1200; t++) {
  const a = Array.from({ length: rand(60) }, () => rand(13) - 6);
  assert.deepEqual(closestBlockingBeacon(a), oracle(a), JSON.stringify(a));
}

const n = 150000;
const increasing = Array.from({ length: n }, (_, i) => i);
const decreasing = Array.from({ length: n }, (_, i) => n - i);
assert.deepEqual(closestBlockingBeacon(increasing), Array(n).fill(-1));
const got = closestBlockingBeacon(decreasing);
assert.equal(got.length, n);
for (let i = 0; i < n; i++) assert.equal(got[i], i - 1);
console.log("PASS easy: fixed, 1200 seeded oracle cases, 150k monotone stress");
