"use strict";
const assert = require("node:assert/strict");
const { longestCompatibleBatch } = require("./solution");
function brute(tags,k){
  let start=0,length=0;
  for(let l=0;l<tags.length;l++){
    const seen=new Set();
    for(let r=l;r<tags.length;r++){
      seen.add(tags[r]);
      if(seen.size<=k && r-l+1>length){start=l;length=r-l+1;}
    }
  }
  return [start,length];
}
function check(tags,k,expected){
  const before=tags.slice();
  assert.deepEqual(longestCompatibleBatch(tags,k),expected,JSON.stringify({tags,k}));
  assert.deepEqual(tags,before,"must not mutate tags");
}
check([2,3,2,1,1,4],2,[0,3]);
check([1,2,1,3,4,3,3],2,[3,4]);
check([7,7,8],1,[0,2]);
check([7,8],0,[0,0]);
check([],3,[0,0]);
check([-1,-2,-1,-3],2,[0,3]);
check([1,2,3],5,[0,3]);
check([9,9,9],1,[0,3]);
let seed=1847;
function rand(){seed=(Math.imul(seed,1103515245)+12345)>>>0;return seed;}
for(let t=0;t<900;t++){
  const a=Array.from({length:rand()%22},()=>rand()%7-3);
  const k=rand()%8;
  check(a,k,brute(a,k));
}
console.log("medium: longest-compatible-batch tests passed");
