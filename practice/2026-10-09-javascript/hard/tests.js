"use strict";
const assert = require("node:assert/strict");
const { minimumPeakDelay } = require("./solution");
// Independent exact-hop dynamic-programming oracle for small randomized graphs.
function brute(n,edges,k,s,t){
  if(s===t)return 0;
  const INF=Infinity;
  let prev=Array(n).fill(INF);prev[s]=0;
  let best=INF;
  for(let h=1;h<=k;h++){
    const next=Array(n).fill(INF);
    for(const [u,v,w] of edges){
      if(prev[u]!==INF)next[v]=Math.min(next[v],Math.max(prev[u],w));
      if(prev[v]!==INF)next[u]=Math.min(next[u],Math.max(prev[v],w));
    }
    best=Math.min(best,next[t]);prev=next;
  }
  return best===INF?-1:best;
}
function check(n,edges,k,s,t,want){
  const copy=edges.map(e=>e.slice());
  assert.equal(minimumPeakDelay(n,edges,k,s,t),want,JSON.stringify({n,edges,k,s,t}));
  assert.deepEqual(edges,copy,"must not mutate edges");
}
const e=[[0,1,7],[1,4,4],[0,2,2],[2,3,3],[3,4,3]];
check(5,e,2,0,4,7);
check(5,e,3,0,4,3);
check(3,[[0,2,9],[0,1,2],[1,2,2]],1,0,2,9);
check(3,[[0,2,9],[0,1,2],[1,2,2]],2,0,2,2);
check(3,[[0,1,0],[1,2,0]],2,0,2,0);
check(3,[[0,1,0],[1,2,0]],1,0,2,-1);
check(4,[],3,0,3,-1);
check(1,[],0,0,0,0);
check(4,[[0,1,5],[0,1,2],[1,2,8],[2,3,1]],3,0,3,8);
check(4,[[0,1,2],[1,1,0],[2,3,2]],10,0,3,-1);
check(3,[[0,1,1000000000],[1,2,999999999]],2,0,2,1000000000);
let seed=324923;
function rand(){seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed;}
for(let t=0;t<1000;t++){
  const n=1+rand()%8,m=rand()%18,k=rand()%10,s=rand()%n,d=rand()%n;
  const edges=Array.from({length:m},()=>[rand()%n,rand()%n,rand()%14]);
  check(n,edges,k,s,d,brute(n,edges,k,s,d));
}
console.log("hard: hop-limited-resilient-route tests passed");
