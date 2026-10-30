"use strict";
const assert = require("node:assert/strict");
const { criticalRouteCount } = require("./solution");
const MOD=1000000007;

// Independent exhaustive oracle: DFS enumerates complete routes in tiny DAGs.
function oracle(n, edges, start, target) {
  const adj=Array.from({length:n},()=>[]);
  for(const [u,v,w] of edges) adj[u].push([v,w]);
  let best=-Infinity, count=0;
  function dfs(u,score) {
    if(u===target) {
      if(score>best) { best=score; count=1; }
      else if(score===best) count++;
      return;
    }
    for(const [v,w] of adj[u]) dfs(v,score+w);
  }
  dfs(start,0);
  return best===-Infinity?{maxWeight:null,ways:0}:{maxWeight:best,ways:count%MOD};
}
const fixed=[
  [5,[[0,1,2],[0,2,2],[1,3,3],[2,3,3],[3,4,-2],[0,4,1]],0,4,{maxWeight:3,ways:2}],
  [4,[[0,1,-2],[1,3,-4],[0,2,-1],[2,3,-3]],0,3,{maxWeight:-4,ways:1}],
  [3,[[2,0,7]],1,0,{maxWeight:null,ways:0}],
  [4,[[0,3,5],[3,1,-1],[1,2,2]],0,2,{maxWeight:6,ways:1}],
  [3,[[0,1,0],[0,2,0],[1,2,0]],0,2,{maxWeight:0,ways:2}],
  [3,[[0,1,-3],[1,2,-2]],0,0,{maxWeight:0,ways:1}],
  [1,[],0,0,{maxWeight:0,ways:1}],
  [2,[],0,1,{maxWeight:null,ways:0}]
];
for(const [n,edges,s,t,want] of fixed) {
  const before=JSON.stringify(edges);
  assert.deepEqual(criticalRouteCount(n,edges,s,t),want);
  assert.equal(JSON.stringify(edges),before,"mutated input");
}

let seed=20261030;
function rand(n) { seed=(Math.imul(seed,1664525)+1013904223)>>>0; return seed%n; }
for(let t=0;t<1300;t++) {
  const n=1+rand(8), order=Array.from({length:n},(_,i)=>i);
  // Fisher-Yates: graph labels deliberately do not follow topo order.
  for(let i=n-1;i>0;i--) { const j=rand(i+1); [order[i],order[j]]=[order[j],order[i]]; }
  const edges=[];
  for(let i=0;i<n;i++) for(let j=i+1;j<n;j++) {
    if(rand(4)===0) edges.push([order[i],order[j],rand(13)-6]);
  }
  const s=rand(n), target=rand(n), before=JSON.stringify(edges);
  assert.deepEqual(criticalRouteCount(n,edges,s,target),oracle(n,edges,s,target),
    JSON.stringify({n,edges,s,target}));
  assert.equal(JSON.stringify(edges),before,"mutated input");
}
// Stress: long chain, including negative scores; recursive DFS may overflow.
const n=120000;
const chain=Array.from({length:n-1},(_,i)=>[i,i+1,-1]);
assert.deepEqual(criticalRouteCount(n,chain,0,n-1),{maxWeight:-(n-1),ways:1});
// Layered diamond: exponentially many equal routes, but linear-size graph.
const layers=40, sink=2*layers+1, diamonds=[];
diamonds.push([0,1,1],[0,2,1]);
for(let layer=0;layer<layers-1;layer++) {
  const a=1+2*layer,b=a+1,c=a+2,d=a+3;
  diamonds.push([a,c,1],[a,d,1],[b,c,1],[b,d,1]);
}
diamonds.push([sink-2,sink,1],[sink-1,sink,1]);
let expectedWays=1;
for(let i=0;i<layers;i++) expectedWays=(expectedWays*2)%MOD;
assert.deepEqual(criticalRouteCount(sink+1,diamonds,0,sink),
  {maxWeight:layers+1,ways:expectedWays});
console.log("PASS hard: fixed, 1300 seeded DFS-oracle cases, 120k chain, 2^40 routes");
