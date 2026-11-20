"use strict";
const assert=require("node:assert/strict");
const {cheapestRouteAfterOneFlip:solve}=require("./solution");

// Independent Bellman-Ford oracle on 2*n states: 0=unused reversal, 1=used.
function oracle(n,edges,s,t){
  const d=Array(n*2).fill(Infinity);d[s]=0;
  for(let i=0;i<2*n;i++){
    let changed=false;
    for(const [u,v,w] of edges){
      if(d[u]+w<d[v]){d[v]=d[u]+w;changed=true;}
      if(d[n+u]+w<d[n+v]){d[n+v]=d[n+u]+w;changed=true;}
      if(d[v]+w<d[n+u]){d[n+u]=d[v]+w;changed=true;}
    }
    if(!changed)break;
  }
  const result=Math.min(d[t],d[n+t]);
  return Number.isFinite(result)?result:-1;
}
const cases=[
  [1,[],0,0,0],[3,[],0,2,-1],
  [3,[[1,0,4],[1,2,2]],0,2,6],
  [3,[[0,1,5],[2,1,1]],0,2,6],
  [3,[[0,1,7],[1,2,2]],0,2,9],
  [3,[[2,1,4],[1,0,5]],0,2,-1],
  [2,[[1,0,0]],0,1,0],
  [2,[[1,0,7],[1,0,1]],0,1,1],
  [2,[[0,1,15],[1,0,4]],0,1,4],
  [4,[[0,1,7],[2,1,0],[2,3,3]],0,3,10],
  [4,[[0,1,1],[1,2,2],[2,3,3]],0,3,6],
  [2,[[0,0,1],[1,1,1]],0,1,-1],
  [3,[[0,1,1000000000],[2,1,1000000000]],0,2,2000000000]
];
for(const [n,edges,s,t,want] of cases){
  const copy=JSON.stringify(edges);
  assert.equal(solve(n,edges,s,t),want,JSON.stringify({n,edges,s,t}));
  assert.equal(JSON.stringify(edges),copy,"input mutation");
}
let seed=20261120;
function rand(k){seed ^= seed << 13;seed ^= seed >>> 17;seed ^= seed << 5;return (seed >>> 0)%k;}
for(let j=0;j<1600;j++){
  const n=2+rand(8),m=rand(31),edges=[];
  for(let i=0;i<m;i++)edges.push([rand(n),rand(n),rand(13)]);
  const s=rand(n),t=rand(n);
  assert.equal(solve(n,edges,s,t),oracle(n,edges,s,t),JSON.stringify({n,edges,s,t}));
}
const N=110000;
const chain=Array.from({length:N-1},(_,i)=>[i,i+1,1]);
assert.equal(solve(N,chain,0,N-1),N-1);
assert.equal(solve(N,chain,N-1,0),-1);
console.log("PASS hard: deterministic, independent 2-layer Bellman-Ford oracle, large stress");

