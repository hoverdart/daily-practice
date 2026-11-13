"use strict";
const assert = require("node:assert/strict");
const { firstFullyConnected } = require("./solution");

(function testEasy(assert,fn){
  function oracle(n,edges){
    if(n<=1)return 0;
    for(let k=1;k<=edges.length;k++){
      const g=Array.from({length:n},()=>[]);
      for(let j=0;j<k;j++){const [u,v]=edges[j];g[u].push(v);g[v].push(u);}
      const seen=new Set([0]),q=[0];
      for(let i=0;i<q.length;i++)for(const v of g[q[i]])if(!seen.has(v)){seen.add(v);q.push(v);}
      if(seen.size===n)return k;
    }
    return -1;
  }
  const cases=[
    [0,[],0],[1,[],0],[1,[[0,0]],0],[2,[],-1],
    [2,[[0,0],[0,1]],2],[3,[[0,1],[1,0],[1,2]],3],
    [4,[[0,1],[2,3],[0,2]],3],
    [4,[[0,1],[0,1],[2,3]],-1],
    [5,[[0,1],[1,2],[2,3],[3,4],[0,4]],4]
  ];
  for(const [n,edges,expect] of cases){
    const old=edges.map(x=>x.slice());
    assert.equal(fn(n,edges),expect,JSON.stringify({n,edges}));
    assert.deepEqual(edges,old,"input mutated");
  }
  let seed=20261113;
  function rand(k){seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;return (seed>>>0)%k;}
  for(let t=0;t<1100;t++){
    const n=rand(9),m=rand(27),edges=[];
    if(n>0)for(let j=0;j<m;j++)edges.push([rand(n),rand(n)]);
    assert.equal(fn(n,edges),oracle(n,edges),JSON.stringify({n,edges}));
  }
  const n=100000,edges=Array.from({length:5000},()=>[0,0]);
  for(let i=0;i<n-1;i++)edges.push([i,i+1]);
  assert.equal(fn(n,edges),5000+n-1,"100k chain");
})(assert, firstFullyConnected);
console.log("PASS easy: deterministic, seeded oracle, stress");
