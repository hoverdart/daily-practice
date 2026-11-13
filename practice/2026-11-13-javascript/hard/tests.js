"use strict";
const assert = require("node:assert/strict");
const { minimumAlternatingRoute } = require("./solution");

(function testHard(assert,fn){
  function oracle(n,edges,source,target){
    if(source===target)return 0;
    const dist=Array(2*n).fill(Infinity);
    dist[2*source]=0;dist[2*source+1]=0;
    for(let k=0;k<2*n-1;k++){
      let changed=false;
      for(const [u,v,w,band] of edges){
        const from=2*u+(1-band),to=2*v+band;
        if(dist[from]+w<dist[to]){dist[to]=dist[from]+w;changed=true;}
      }
      if(!changed)break;
    }
    const result=Math.min(dist[2*target],dist[2*target+1]);
    return result===Infinity?-1:result;
  }
  const cases=[
    [1,[],0,0,0],[2,[],0,1,-1],
    [2,[[0,1,7,0]],0,1,7],
    [3,[[0,1,4,0],[1,2,9,0]],0,2,-1],
    [3,[[0,1,4,0],[1,2,9,1]],0,2,13],
    [4,[[0,1,1,0],[1,3,1,0],[0,2,4,0],[2,1,1,1]],0,3,6],
    [2,[[0,1,0,0],[0,1,4,1]],0,1,0],
    [3,[[0,1,1,1],[1,2,1,0],[0,2,6,0]],0,2,2],
    [3,[[0,0,0,0],[0,1,0,1],[1,2,0,0]],0,2,0],
    [3,[[2,1,3,1],[1,0,5,0]],2,0,8],
    [3,[[0,1,5,0],[1,0,0,1]],0,2,-1]
  ];
  for(const [n,edges,s,t,expect] of cases){
    const old=edges.map(x=>x.slice());
    assert.equal(fn(n,edges,s,t),expect,JSON.stringify({n,edges,s,t}));
    assert.deepEqual(edges,old,"input mutated");
  }
  let seed=20261113;
  function rand(k){seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;return(seed>>>0)%k;}
  for(let t=0;t<1000;t++){
    const n=rand(8)+1,m=rand(32),edges=[];
    for(let j=0;j<m;j++)edges.push([rand(n),rand(n),rand(12),rand(2)]);
    const s=rand(n),target=rand(n);
    assert.equal(fn(n,edges,s,target),oracle(n,edges,s,target),JSON.stringify({n,edges,s,target}));
  }
  const n=65000;
  assert.equal(fn(n,Array.from({length:n-1},(_,i)=>[i,i+1,1,i%2]),0,n-1),n-1,"alternating chain");
  const k=25000;
  assert.equal(fn(k,Array.from({length:k-1},(_,i)=>[i,i+1,1,0]),0,k-1),-1,"same-band chain");
})(assert, minimumAlternatingRoute);
console.log("PASS hard: deterministic, seeded oracle, stress");
