"use strict";

function cheapestRouteAfterOneFlip(n, edges, source, target) {
  if (source===target) return 0;
  const out=Array.from({length:n},()=>[]),incoming=Array.from({length:n},()=>[]);
  for(const [u,v,w] of edges) { out[u].push([v,w]); incoming[v].push([u,w]); }
  function dijkstra(start, graph) {
    const dist=Array(n).fill(Infinity);
    const heap=[];
    function push(d,u) {
      let i=heap.length; heap.push([d,u]);
      while(i>0) {
        let p=(i-1)>>1;
        if(heap[p][0]<=d) break;
        heap[i]=heap[p]; i=p;
      }
      heap[i]=[d,u];
    }
    function pop() {
      const result=heap[0], tail=heap.pop();
      if(heap.length) {
        let i=0;
        while(2*i+1<heap.length) {
          let j=2*i+1;
          if(j+1<heap.length && heap[j+1][0]<heap[j][0]) j++;
          if(heap[j][0]>=tail[0]) break;
          heap[i]=heap[j]; i=j;
        }
        heap[i]=tail;
      }
      return result;
    }
    dist[start]=0; push(0,start);
    while(heap.length) {
      const [d,u]=pop();
      if(d!==dist[u]) continue;
      for(const [v,w] of graph[u]) {
        const nd=d+w;
        if(nd<dist[v]) { dist[v]=nd; push(nd,v); }
      }
    }
    return dist;
  }
  const from=dijkstra(source,out);
  const toTarget=dijkstra(target,incoming);
  let best=from[target];
  for(const [u,v,w] of edges) {
    if(Number.isFinite(from[v]) && Number.isFinite(toTarget[u])) {
      best=Math.min(best,from[v]+w+toTarget[u]);
    }
  }
  return Number.isFinite(best)?best:-1;
}

module.exports = { cheapestRouteAfterOneFlip };
