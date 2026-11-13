"use strict";

function firstFullyConnected(n,links){
  if(n<=1)return 0;
  const parent=Array.from({length:n},(_,i)=>i), size=Array(n).fill(1);
  let groups=n;
  function find(x){while(parent[x]!==x){parent[x]=parent[parent[x]];x=parent[x];}return x;}
  for(let i=0;i<links.length;i++){
    let a=find(links[i][0]),b=find(links[i][1]);
    if(a!==b){
      if(size[a]<size[b])[a,b]=[b,a];
      parent[b]=a;size[a]+=size[b];groups--;
    }
    if(groups===1)return i+1;
  }
  return -1;
}

module.exports = { firstFullyConnected };
