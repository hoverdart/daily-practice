"use strict";
const assert = require("node:assert/strict");
const { cheapestRefundRoute: solve } = require("./solution");

function hardTests(solve, assert) {
  function oracle(n,edges,s,t) {
    const d=Array.from({length:n},(_,i)=>Array.from({length:n},(_,j)=>i===j?0:Infinity));
    for(const [u,v,w] of edges) d[u][v]=Math.min(d[u][v],w);
    for(let k=0;k<n;k++) for(let i=0;i<n;i++) for(let j=0;j<n;j++)
      d[i][j]=Math.min(d[i][j],d[i][k]+d[k][j]);
    if(d[s][t]===Infinity) return null;
    for(let k=0;k<n;k++) if(d[s][k]!==Infinity&&d[k][k]<0&&d[k][t]!==Infinity)
      return "UNBOUNDED";
    return d[s][t];
  }
  const fixed=[
    [1,[],0,0,0],[1,[[0,0,-1]],0,0,"UNBOUNDED"],
    [3,[[0,1,5],[0,2,2],[1,2,-10]],0,2,-5],
    [4,[[0,1,1],[1,1,-1],[0,3,6]],0,3,6],
    [4,[[0,3,8],[1,1,-2],[1,3,0]],0,3,8],
    [4,[[0,1,2],[1,2,-5],[2,1,1],[2,3,7]],0,3,"UNBOUNDED"],
    [3,[[0,1,-9],[1,1,-1]],0,2,null],
    [3,[[0,1,9],[0,1,2],[1,2,-2]],0,2,0],
    [3,[[0,1,-4],[1,0,4],[1,2,1]],0,2,-3],
    [2,[[0,1,-3]],1,0,null],[2,[[0,1,-3],[1,0,1]],0,0,"UNBOUNDED"],
    [3,[[0,1,-1000000],[1,2,-1000000]],0,2,-2000000]
  ];
  for(const [n,e,s,t,expected] of fixed) {
    assert.equal(oracle(n,e,s,t),expected);
    assert.equal(solve(n,e,s,t),expected);
  }
  let seed=117272026;
  function rand(k) { seed ^= seed<<13; seed ^= seed>>>17; seed ^= seed<<5; return (seed>>>0)%k; }
  for(let t=0;t<2000;t++) {
    const n=1+rand(8), edges=Array.from({length:rand(n*n+1)},()=>[rand(n),rand(n),rand(17)-8]);
    const s=rand(n), dest=rand(n);
    assert.equal(solve(n,edges,s,dest),oracle(n,edges,s,dest));
  }
  const n=2000, chain=[];
  for(let i=n-2;i>=0;i--) chain.push([i,i+1,i%2===0?-3:2]);
  assert.equal(solve(n,chain,0,n-1),chain.reduce((sum,e)=>sum+e[2],0));
  assert.equal(solve(n,[...chain,[1000,1000,-1]],0,n-1),"UNBOUNDED");
  const irrelevant=Array.from({length:1998},(_,i)=>[i,i+1,-1]);
  irrelevant.push([100,100,-1],[0,1999,4]);
  assert.equal(solve(n,irrelevant,0,1999),4);
  return {fixed:fixed.length,random:2000,stress:3};
}

console.log("PASS hard", hardTests(solve, assert));
