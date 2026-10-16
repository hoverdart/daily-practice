"use strict";
const assert = require("node:assert/strict");
const { firstNearbyDuplicate } = require("./solution");
function brute(a,k) {
  for (let j=0;j<a.length;j++)
    for (let i=Math.max(0,j-k);i<j;i++)
      if (a[i]===a[j]) return j;
  return -1;
}
const cases = [
  [[8,3,5,8,3],3,3], [[4,7,4],1,-1], [[2,2],0,-1],
  [[5,1,5,1],2,2], [[],3,-1], [[1],5,-1],
  [[-5,0,-5],2,2], [[1,2,3,1],2,-1], [[1,2,3,1],3,3],
  [[9,9,9],1,1], [[1,2,1,2],1,-1]
];
for(const [a,k,want] of cases) assert.equal(firstNearbyDuplicate(a,k),want);
let seed=20261016;
const rnd=()=>{seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed/4294967296;};
const ri=n=>Math.floor(rnd()*n);
for(let t=0;t<600;t++){
  const a=Array.from({length:ri(32)},()=>ri(11)-5),k=ri(18);
  assert.equal(firstNearbyDuplicate(a,k),brute(a,k),JSON.stringify({a,k}));
}
assert.equal(firstNearbyDuplicate(Array.from({length:200000},(_,i)=>i),100),-1);
console.log("PASS easy: fixed, 600 seeded oracle cases, 200k stress");
