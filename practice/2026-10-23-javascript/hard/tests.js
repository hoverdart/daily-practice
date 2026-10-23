"use strict";
const assert = require("node:assert/strict");
const { cheapestVoucherRoute } = require("./solution");

// Independent Bellman-Ford oracle on a two-layer graph, for small instances.
function oracle(n, edges, start, goal) {
  const d = Array(2*n).fill(Infinity);
  d[2*start]=0;
  for(let pass=0;pass<2*n-1;pass++){
    let changed=false;
    for(const [u,v,w] of edges){
      for(let used=0;used<=1;used++){
        const a=2*u+used,b=2*v+used;
        if(d[a]+w<d[b]){d[b]=d[a]+w;changed=true;}
        if(used===0 && d[a]<d[2*v+1]){
          d[2*v+1]=d[a];changed=true;
        }
      }
    }
    if(!changed)break;
  }
  return Number.isFinite(d[2*goal+1])?d[2*goal+1]:-1;
}
const fixed=[
  [4,[[0,1,8],[1,3,5],[0,2,3],[2,3,20]],0,3,3],
  [2,[],0,0,-1],
  [2,[[0,1,4],[1,0,7]],0,0,4],
  [1,[[0,0,12]],0,0,0],
  [2,[[0,1,100],[0,1,2]],0,1,0],
  [3,[[0,1,3]],0,2,-1],
  [3,[[0,1,2],[1,2,5]],0,2,2],
  [1,[],0,0,-1],
  [3,[[0,1,5],[1,0,9],[1,2,1]],2,2,-1]
];
for(const [n,edges,s,t,want] of fixed)
  assert.equal(cheapestVoucherRoute(n,edges,s,t),want,JSON.stringify({n,edges,s,t}));
let seed=20261023;
const ri=n=>{seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed%n;};
for(let run=0;run<1300;run++){
  const n=1+ri(9),m=ri(25);
  const edges=Array.from({length:m},()=>[ri(n),ri(n),1+ri(25)]);
  const start=ri(n),goal=ri(n);
  const before=JSON.stringify(edges);
  assert.equal(cheapestVoucherRoute(n,edges,start,goal),
    oracle(n,edges,start,goal),JSON.stringify({n,edges,start,goal}));
  assert.equal(JSON.stringify(edges),before,"mutated input");
}
const n=80000;
const chain=Array.from({length:n-1},(_,i)=>[i,i+1,3]);
assert.equal(cheapestVoucherRoute(n,chain,0,n-1),(n-2)*3);
console.log("PASS hard: fixed, 1300 seeded independent Bellman-Ford cases, 80k stress");

