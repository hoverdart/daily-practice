"use strict";

const MOD=1000000007;

function criticalRouteCount(n, edges, start, target) {
  const adj=Array.from({length:n},()=>[]);
  const indegree=Array(n).fill(0);
  for(const [u,v,w] of edges) {
    adj[u].push([v,w]);
    indegree[v]++;
  }
  const best=Array(n).fill(-Infinity);
  const ways=Array(n).fill(0);
  best[start]=0;
  ways[start]=1;

  const queue=[];
  for(let i=0;i<n;i++) if(indegree[i]===0) queue.push(i);
  let head=0;
  while(head<queue.length) {
    const u=queue[head++];
    for(const [v,w] of adj[u]) {
      if(best[u]!==-Infinity) {
        const candidate=best[u]+w;
        if(candidate>best[v]) {
          best[v]=candidate;
          ways[v]=ways[u];
        } else if(candidate===best[v]) {
          ways[v]=(ways[v]+ways[u])%MOD;
        }
      }
      indegree[v]--;
      if(indegree[v]===0) queue.push(v);
    }
  }
  if(best[target]===-Infinity) return {maxWeight:null,ways:0};
  return {maxWeight:best[target],ways:ways[target]};
}

module.exports = { criticalRouteCount };
