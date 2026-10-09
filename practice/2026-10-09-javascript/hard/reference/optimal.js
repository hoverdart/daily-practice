"use strict";
function minimumPeakDelay(n,edges,maxHops,source,target){
  if(source===target)return 0;
  if(maxHops<=0)return -1;
  const graph=Array.from({length:n},()=>[]);
  let maxDelay=0;
  for(const [u,v,w] of edges){
    graph[u].push([v,w]);
    graph[v].push([u,w]);
    if(w>maxDelay)maxDelay=w;
  }
  const hopsAllowed=Math.min(maxHops,n-1);
  function reachable(threshold){
    const dist=new Int32Array(n);
    dist.fill(-1);
    const queue=new Int32Array(n);
    let head=0,tail=0;
    queue[tail++]=source;dist[source]=0;
    while(head<tail){
      const u=queue[head++];
      if(dist[u]===hopsAllowed)continue;
      for(const [v,w] of graph[u]){
        if(w>threshold || dist[v]!==-1)continue;
        dist[v]=dist[u]+1;
        if(v===target)return true;
        queue[tail++]=v;
      }
    }
    return false;
  }
  if(!reachable(maxDelay))return -1;
  let lo=0,hi=maxDelay;
  while(lo<hi){
    const mid=lo+Math.floor((hi-lo)/2);
    if(reachable(mid))hi=mid;
    else lo=mid+1;
  }
  return lo;
}
module.exports = { minimumPeakDelay };
