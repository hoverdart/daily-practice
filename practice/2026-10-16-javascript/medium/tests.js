"use strict";
const assert = require("node:assert/strict");
const { processPrefixOperations } = require("./solution");
function oracle(ops) {
  const counts=new Map(),out=[];
  for(const [action,w] of ops){
    if(action==="add") counts.set(w,(counts.get(w)||0)+1);
    else if(action==="remove"){if((counts.get(w)||0)>0) counts.set(w,counts.get(w)-1);}
    else {
      let n=0;
      for(const [word,count] of counts) if(word.startsWith(w)) n+=count;
      out.push(n);
    }
  }
  return out;
}
const examples=[
 [["add","cam"],["add","camera"],["add","cam"],["count","cam"],["remove","cam"],["count","cam"],["count","camera"],["remove","missing"],["count",""]],
 [["count",""],["remove","a"],["count","a"]],
 [["add","abc"],["remove","ab"],["count","ab"],["remove","abc"],["count",""]],
 [["add","a"],["add","a"],["remove","a"],["count","a"],["remove","a"],["count","a"],["remove","a"],["count",""]]
];
for(const ops of examples) assert.deepEqual(processPrefixOperations(ops),oracle(ops));
let seed=12026016;
const rnd=()=>{seed=(Math.imul(seed,1103515245)+12345)>>>0;return seed/4294967296;};
const ri=n=>Math.floor(rnd()*n);
for(let t=0;t<450;t++){
  const ops=Array.from({length:ri(80)},()=>{
    const action=["add","remove","count"][ri(3)];
    const word=Array.from({length:ri(5)+(action==="count"?0:1)},()=>String.fromCharCode(97+ri(4))).join("");
    return [action,word];
  });
  assert.deepEqual(processPrefixOperations(ops),oracle(ops),JSON.stringify(ops));
}
const big=[];
for(let i=0;i<30000;i++) big.push(["add","x"+String(i).padStart(5,"0").replace(/[0-9]/g,d=>String.fromCharCode(97+Number(d)))]);
big.push(["count","x"],["count",""]);
assert.deepEqual(processPrefixOperations(big),[30000,30000]);
console.log("PASS medium: fixed, 450 seeded oracle cases, 30k inserts");
