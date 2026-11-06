"use strict";
const assert = require("node:assert/strict");
const { minimumCompliantSwitchCost } = require("./solution");

// Independent brute-force oracle enumerating legal sequences for n <= 7.
function oracle(costs, prerequisites) {
  const n = costs.length;
  const needed = Array(n).fill(0);
  for (const [a,b] of prerequisites) needed[b] |= 1 << a;
  let best = Infinity;
  function search(used, last, cost) {
    if (used === (1 << n) - 1) {
      best = Math.min(best, cost);
      return;
    }
    for (let next = 0; next < n; next++) {
      const bit = 1 << next;
      if ((used & bit) !== 0) continue;
      if ((needed[next] & used) !== needed[next]) continue;
      search(used | bit, next, cost + (last < 0 ? 0 : costs[last][next]));
    }
  }
  search(0, -1, 0);
  return Number.isFinite(best) ? best : -1;
}
function check(costs, edges, expected) {
  const prevCosts = costs.map(row => row.slice()), prevEdges = edges.map(e => e.slice());
  assert.equal(minimumCompliantSwitchCost(costs, edges), expected, JSON.stringify({costs, edges}));
  assert.deepEqual(costs, prevCosts, "cost matrix changed");
  assert.deepEqual(edges, prevEdges, "prerequisites changed");
}

check([], [], 0);
check([[0]], [], 0);
check([[0]], [[0,0]], -1);
check([[0,8,1],[2,0,2],[4,3,0]], [[0,2]], 3);
check([[0,8,1],[2,0,2],[4,3,0]], [[0,2],[0,2]], 3);
check([[0,5],[9,0]], [], 5);
check([[0,5],[9,0]], [[1,0]], 9);
check([[0,5],[9,0]], [[0,1]], 5);
check([[0,5],[9,0]], [[0,1],[1,0]], -1);
check([[0,4,4],[4,0,4],[4,4,0]], [[0,1],[1,2],[2,0]], -1);

let seed = 20261106;
function rand(n) { seed = (Math.imul(seed, 1103515245) + 12345) >>> 0; return seed % n; }
for (let t = 0; t < 450; t++) {
  const n = rand(8);
  const costs = Array.from({length:n}, () => Array.from({length:n}, () => rand(20)));
  const edges = [];
  for (let a = 0; a < n; a++) for (let b = 0; b < n; b++) {
    if (rand(13) === 0) edges.push([a,b]);
  }
  check(costs, edges, oracle(costs, edges));
}

const n = 15;
const zero = Array.from({length:n}, () => Array(n).fill(0));
check(zero, [], 0);
const ones = Array.from({length:n}, (_, i) => Array.from({length:n}, (_, j) => i === j ? 0 : 1));
check(ones, [], n-1);
const chain = Array.from({length:n-1}, (_,i) => [i,i+1]);
const directional = Array.from({length:n}, (_,i) => Array.from({length:n}, (_,j) => (i*17+j*7)%101));
let chainCost = 0;
for (let i=0;i<n-1;i++) chainCost += directional[i][i+1];
check(directional, chain, chainCost);
console.log("PASS hard: fixed, 450 seeded brute-force oracle cases, n=15 stress");
