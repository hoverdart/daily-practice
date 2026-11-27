"use strict";
const assert = require("node:assert/strict");
const { calibrationNeighbors: solve } = require("./solution");

function easyTests(solve, assert) {
  function insert(root, key) {
    if (root === null) return {key, left:null, right:null};
    let p = root;
    while (true) {
      if (key === p.key) return root;
      const side = key < p.key ? "left" : "right";
      if (p[side] === null) { p[side] = {key,left:null,right:null}; return root; }
      p = p[side];
    }
  }
  function tree(keys) { return keys.reduce((r,k)=>insert(r,k),null); }
  const r=tree([12,4,18,7,15]);
  const fixed=[
    [null,8,[null,null]],[r,8,[7,12]],[r,12,[12,12]],[r,-5,[null,4]],
    [r,20,[18,null]],[tree([0]),0,[0,0]],[tree([-9,-3]),-5,[-9,-3]],
    [tree([1000000000,-1000000000]),0,[-1000000000,1000000000]]
  ];
  for(const [root,target,expected] of fixed) assert.deepEqual(solve(root,target),expected);
  let seed=20261127;
  function rand(k) { seed ^= seed<<13; seed ^= seed>>>17; seed ^= seed<<5; return (seed>>>0)%k; }
  for(let t=0;t<1400;t++) {
    const keys=Array.from({length:rand(60)},()=>rand(201)-100);
    const target=rand(241)-120;
    const lower=keys.filter(x=>x<=target), upper=keys.filter(x=>x>=target);
    const expected=[lower.length?Math.max(...lower):null,upper.length?Math.min(...upper):null];
    assert.deepEqual(solve(tree(keys),target),expected);
  }
  let skew=null;
  for(let i=99999;i>=0;i--) skew={key:2*i,left:null,right:skew};
  assert.deepEqual(solve(skew,199997),[199996,199998]);
  assert.deepEqual(solve(skew,200000),[199998,null]);
  return {fixed:fixed.length,random:1400,stress:2};
}

console.log("PASS easy", easyTests(solve, assert));
