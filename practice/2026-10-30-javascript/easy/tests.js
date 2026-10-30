"use strict";
const assert = require("node:assert/strict");
const { closestSharedSupervisor } = require("./solution");

// Independent oracle: build root-to-node paths and compare common prefixes.
function oracle(parent, a, b) {
  function rootPath(x) {
    const path = [];
    while (x !== -1) { path.push(x); x = parent[x]; }
    return path.reverse();
  }
  const pa = rootPath(a), pb = rootPath(b);
  let answer = -1;
  for (let i = 0; i < Math.min(pa.length, pb.length); i++) {
    if (pa[i] !== pb[i]) break;
    answer = pa[i];
  }
  return answer;
}

const p = [-1,0,0,1,1,2,-1,6];
for (const [a,b,want] of [[3,4,1],[3,5,0],[3,7,-1],[2,2,2],[0,1,0],[6,7,6],[7,6,6]]) {
  assert.equal(closestSharedSupervisor(p,a,b),want);
}
assert.deepEqual(p,[-1,0,0,1,1,2,-1,6],"input mutated");
assert.equal(closestSharedSupervisor([-1],0,0),0);
assert.equal(closestSharedSupervisor([-1,-1],0,1),-1);

let seed = 20261030;
function rand(n) { seed = (Math.imul(seed,1664525)+1013904223)>>>0; return seed%n; }
for (let t=0;t<1200;t++) {
  const n=1+rand(75), parent=[-1];
  for(let i=1;i<n;i++) parent.push(rand(5)===0?-1:rand(i));
  const a=rand(n), b=rand(n), copy=parent.slice();
  assert.equal(closestSharedSupervisor(parent,a,b),oracle(parent,a,b),JSON.stringify({parent,a,b}));
  assert.deepEqual(parent,copy,"input mutated");
}
// Worst-case depth: recursion-based solutions typically overflow JS call stacks.
const n=120000, chain=Array.from({length:n},(_,i)=>i===0?-1:i-1);
assert.equal(closestSharedSupervisor(chain,n-1,n-3000),n-3000);
assert.equal(closestSharedSupervisor(chain,n-1,0),0);
console.log("PASS easy: fixed, 1200 seeded oracle cases, 120k-depth stress");
