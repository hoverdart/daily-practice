"use strict";
const assert = require("node:assert/strict");
const { longestRecalibratableRun } = require("./solution");

// Independent exhaustive oracle: enumerate every interval, count its exact mode.
function oracle(codes,k) {
  let best=0;
  for(let l=0;l<codes.length;l++) {
    const count=new Map(); let mode=0;
    for(let r=l;r<codes.length;r++) {
      const c=(count.get(codes[r])||0)+1;
      count.set(codes[r],c); mode=Math.max(mode,c);
      if(r-l+1-mode<=k) best=Math.max(best,r-l+1);
    }
  }
  return best;
}

const fixed=[
  [[],0,0],[[9,9,9],0,3],[[4,5,4,5,4,5],1,3],
  [[1,2,2,1,2,2,2],1,6],[[1,2,3,4],4,4],
  [[1,2,3,4],0,1],[[5,5,1,1,1,5,5],2,5],
  [[-1,-1,1000000000,-1],1,4],[[7],0,1],[[7],1,1],
  [[1,1,2,3,3,3,2,2,2,2],2,6]
];
for(const [codes,k,want] of fixed) {
  const before=codes.slice();
  assert.equal(longestRecalibratableRun(codes,k),want,JSON.stringify({codes,k}));
  assert.deepEqual(codes,before,"input mutated");
}
let seed=30302026;
function rand(n) { seed=(Math.imul(seed,1664525)+1013904223)>>>0; return seed%n; }
for(let t=0;t<1600;t++) {
  const n=rand(37), codes=Array.from({length:n},()=>rand(8)-3), k=rand(n+1);
  const snapshot=codes.slice();
  assert.equal(longestRecalibratableRun(codes,k),oracle(codes,k),JSON.stringify({codes,k}));
  assert.deepEqual(codes,snapshot,"input mutated");
}
const n=120000;
const unique=Array.from({length:n},(_,i)=>i);
assert.equal(longestRecalibratableRun(unique,3),4);
assert.equal(longestRecalibratableRun(Array(n).fill(42),0),n);
assert.equal(longestRecalibratableRun(Array.from({length:n},(_,i)=>i%2),2),5);
console.log("PASS medium: fixed, 1600 seeded exhaustive-oracle cases, 120k stress");
