"use strict";
const assert = require("node:assert/strict");
const { longestExactNetRun } = require("./solution");

(function testMedium(assert,fn){
  function oracle(a,target){
    let best=[-1,-1],len=0;
    for(let i=0;i<a.length;i++){
      let sum=0;
      for(let j=i;j<a.length;j++){
        sum+=a[j];
        if(sum===target&&(j+1-i>len||(j+1-i===len&&(best[0]===-1||i<best[0])))){
          len=j+1-i;best=[i,j+1];
        }
      }
    }
    return best;
  }
  const cases=[
    [[],0,[-1,-1]],[[0],0,[0,1]],[[3],5,[-1,-1]],
    [[1,2,3],3,[0,2]],[[2,-3,1,4,-4],0,[0,5]],
    [[1,-1,3,1,-1],3,[0,5]],
    [[2,1,5,2,1],3,[0,2]],
    [[-2,3,-1,7],0,[0,3]],[[2,-1,2],2,[0,1]],
    [[1,1,1],5,[-1,-1]],
    [[-1000000,1000000,-1000000,1000000],0,[0,4]]
  ];
  for(const [a,target,expect] of cases){
    const old=a.slice();
    assert.deepEqual(fn(a,target),expect,JSON.stringify({a,target}));
    assert.deepEqual(a,old,"input mutated");
  }
  let seed=13112026;
  function rand(k){seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;return(seed>>>0)%k;}
  for(let t=0;t<1400;t++){
    const a=Array.from({length:rand(45)},()=>rand(15)-7),target=rand(35)-17;
    assert.deepEqual(fn(a,target),oracle(a,target),JSON.stringify({a,target}));
  }
  const n=140000;
  const a=Array.from({length:n},(_,i)=>i%2===0?1000000:-1000000);
  assert.deepEqual(fn(a,0),[0,n],"large signed alternating case");
  assert.deepEqual(fn(Array(n).fill(1),n+1),[-1,-1],"no match stress");
})(assert, longestExactNetRun);
console.log("PASS medium: deterministic, seeded oracle, stress");
