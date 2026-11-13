"use strict";

class MinHeap{
  constructor(){this.a=[];}
  get length(){return this.a.length;}
  push(item){
    const a=this.a;let i=a.length;a.push(item);
    while(i>0){const p=(i-1)>>1;if(a[p][0]<=item[0])break;a[i]=a[p];i=p;}
    a[i]=item;
  }
  pop(){
    const a=this.a,result=a[0],last=a.pop();
    if(a.length){
      let i=0;
      while(2*i+1<a.length){
        let c=2*i+1;
        if(c+1<a.length&&a[c+1][0]<a[c][0])c++;
        if(a[c][0]>=last[0])break;
        a[i]=a[c];i=c;
      }
      a[i]=last;
    }
    return result;
  }
}

function minimumAlternatingRoute(n,edges,source,target){
  if(source===target)return 0;
  const graph=Array.from({length:n},()=>[]);
  for(const [u,v,w,band] of edges)graph[u].push([v,w,band]);
  const dist=Array(2*n).fill(Infinity),heap=new MinHeap();
  for(let last=0;last<2;last++){
    const state=2*source+last;dist[state]=0;heap.push([0,state]);
  }
  while(heap.length){
    const [cost,state]=heap.pop();
    if(cost!==dist[state])continue;
    const u=Math.floor(state/2),last=state%2;
    if(u===target)return cost;
    for(const [v,w,band] of graph[u]){
      if(band===last)continue;
      const next=2*v+band,nd=cost+w;
      if(nd<dist[next]){dist[next]=nd;heap.push([nd,next]);}
    }
  }
  return -1;
}

module.exports = { minimumAlternatingRoute };
