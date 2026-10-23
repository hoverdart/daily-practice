"use strict";
const assert = require("node:assert/strict");
const { shortestRequiredSignalWindow } = require("./solution");

function oracle(events, required) {
  if (!required.length) return [0,-1];
  const counts = new Map();
  for (const x of required) counts.set(x,(counts.get(x)||0)+1);
  let best=[-1,-1], bestLen=Infinity;
  for(let l=0;l<events.length;l++){
    const seen=new Map();
    for(let r=l;r<events.length;r++){
      seen.set(events[r],(seen.get(events[r])||0)+1);
      if([...counts].every(([x,c])=>(seen.get(x)||0)>=c)){
        if(r-l+1<bestLen){bestLen=r-l+1;best=[l,r];}
        break;
      }
    }
  }
  return best;
}
const fixed=[
  [[4,7,2,7,3,7,2],[7,7,3],[3,5]],
  [[2,1,3,2,1,3],[1,2],[0,1]],
  [[9,8,9],[9,9,9],[-1,-1]],
  [[],[],[0,-1]],
  [[2,3],[],[0,-1]],
  [[],[1],[-1,-1]],
  [[1,1,1],[1,1],[0,1]],
  [[-3,5,-3,5],[-3,5],[0,1]],
  [[1,2,1,2],[1,1],[0,2]],
  [[4,5,6],[6],[2,2]]
];
for(const [events,required,want] of fixed)
  assert.deepEqual(shortestRequiredSignalWindow(events,required),want);
let seed=20261023;
const ri=n=>{seed=(Math.imul(seed,1103515245)+12345)>>>0;return seed%n;};
for(let t=0;t<1100;t++){
  const events=Array.from({length:ri(16)},()=>ri(7)-3);
  const required=Array.from({length:ri(7)},()=>ri(7)-3);
  const before=JSON.stringify([events,required]);
  assert.deepEqual(shortestRequiredSignalWindow(events,required),
    oracle(events,required),before);
  assert.equal(JSON.stringify([events,required]),before,"mutated input");
}
const big=Array.from({length:200000},(_,i)=>[1,2,3,2][i%4]);
assert.deepEqual(shortestRequiredSignalWindow(big,[1,2,2,3]),[0,3]);
console.log("PASS medium: fixed, 1100 seeded independent-oracle cases, 200k stress");

