"use strict";
const assert = require("node:assert/strict");
const { firstCapacityIndex } = require("./solution");

function check(a, limit, expected) {
  const original = a.slice();
  assert.equal(firstCapacityIndex(a, limit), expected, JSON.stringify({a,limit}));
  assert.deepEqual(a, original, "input must not be modified");
}
check([1,3,3,8,11],3,1);
check([1,3,3,8,11],9,4);
check([2,2,2],1,0);
check([2,2,2],2,0);
check([2,2,2],3,-1);
check([],0,-1);
check([-9,-5,-5,-1],-5,1);
check([0],0,0);
check([0],1,-1);
let seed=20261009;
function rand(){seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed;}
for(let t=0;t<600;t++){
  const n=rand()%35;
  const a=[]; let cur=-30;
  for(let i=0;i<n;i++){cur+=rand()%4;a.push(cur);}
  const limit=(rand()%90)-35;
  check(a,limit,a.findIndex(x=>x>=limit));
}
console.log("easy: first-capacity-index tests passed");
