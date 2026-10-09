"use strict";
function longestCompatibleBatch(tags,k){
  if(k<=0 || tags.length===0)return [0,0];
  const freq=new Map();
  let left=0,bestStart=0,bestLength=0;
  for(let right=0;right<tags.length;right++){
    const tag=tags[right];
    freq.set(tag,(freq.get(tag)??0)+1);
    while(freq.size>k){
      const old=tags[left++];
      const next=freq.get(old)-1;
      if(next===0)freq.delete(old);
      else freq.set(old,next);
    }
    const length=right-left+1;
    if(length>bestLength){bestLength=length;bestStart=left;}
  }
  return [bestStart,bestLength];
}
module.exports = { longestCompatibleBatch };
