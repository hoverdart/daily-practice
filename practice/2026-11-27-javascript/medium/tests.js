"use strict";
const assert = require("node:assert/strict");
const { shortestArchiveCut: solve } = require("./solution");

function mediumTests(solve, assert) {
  function oracle(a,cap) {
    for(let length=0;length<=a.length;length++) {
      for(let left=0;left+length<=a.length;left++) {
        const counts=new Map();
        for(let i=0;i<a.length;i++) if(i<left||i>=left+length)
          counts.set(a[i],(counts.get(a[i])??0)+1);
        if([...counts.values()].every(c=>c<=cap)) return length;
      }
    }
  }
  const fixed=[
    [[],0,0],[[1,2,3],1,0],[[1,2,1,3,2],1,2],
    [[7,7,7,7],2,2],[[1,2,3],0,3],[[1,9,9,1],1,2],
    [[-1,-1,0,0,-1],1,3],[[1,2,3,1,4,2],1,2],
    [[5,5,5],10,0],[[1000000000,-1000000000,1000000000],1,1]
  ];
  for(const [a,c,expected] of fixed) {
    assert.equal(oracle(a,c),expected);
    assert.equal(solve(a,c),expected);
  }
  let seed=27112026;
  function rand(k) { seed ^= seed<<13; seed ^= seed>>>17; seed ^= seed<<5; return (seed>>>0)%k; }
  for(let t=0;t<1800;t++) {
    const a=Array.from({length:rand(15)},()=>rand(7)-3), cap=rand(7);
    assert.equal(solve(a,cap),oracle(a,cap));
  }
  assert.equal(solve(Array.from({length:200000},(_,i)=>i%2),40000),120000);
  assert.equal(solve(Array.from({length:200000},(_,i)=>i),1),0);
  return {fixed:fixed.length,random:1800,stress:2};
}

console.log("PASS medium", mediumTests(solve, assert));
