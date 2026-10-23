"use strict";
const assert = require("node:assert/strict");
const { insertMaintenanceWindow } = require("./solution");

function oracle(intervals, added) {
  const sorted = [...intervals.map(pair => [...pair]), [...added]]
    .sort((a,b) => a[0]-b[0]);
  const out = [];
  for (const [l,r] of sorted) {
    if (out.length && out[out.length-1][1] >= l)
      out[out.length-1][1] = Math.max(out[out.length-1][1],r);
    else out.push([l,r]);
  }
  return out;
}
const fixed = [
  [[[1,3],[7,9],[12,14]],[3,12],[[1,14]]],
  [[[-5,-3],[2,4]],[-1,0],[[-5,-3],[-1,0],[2,4]]],
  [[],[8,8],[[8,8]]],
  [[[1,2],[6,7]],[3,5],[[1,2],[3,5],[6,7]]],
  [[[1,2],[6,7]],[2,6],[[1,7]]],
  [[[0,0]],[0,0],[[0,0]]],
  [[[3,4],[8,9]],[-10,-2],[[-10,-2],[3,4],[8,9]]]
];
for (const [intervals,added,want] of fixed) {
  const snapshot = JSON.stringify([intervals,added]);
  assert.deepEqual(insertMaintenanceWindow(intervals,added),want);
  assert.equal(JSON.stringify([intervals,added]),snapshot,"mutated input");
}
let seed=20261023;
const ri=n=>{seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed%n;};
for(let t=0;t<800;t++){
  const intervals=[];let current=-40;
  const n=ri(35);
  for(let i=0;i<n;i++){
    current+=1+ri(4);
    const end=current+ri(5);
    intervals.push([current,end]);
    current=end+1;
  }
  const l=ri(100)-50, added=[l,l+ri(25)];
  const snapshot=JSON.stringify([intervals,added]);
  assert.deepEqual(insertMaintenanceWindow(intervals,added),oracle(intervals,added),snapshot);
  assert.equal(JSON.stringify([intervals,added]),snapshot,"mutated input");
}
const large=Array.from({length:100000},(_,i)=>[3*i,3*i+1]);
assert.deepEqual(insertMaintenanceWindow(large,[-1,300000]),[[-1,300000]]);
console.log("PASS easy: fixed, 800 seeded independent-oracle cases, 100k stress");

