"use strict";

function longestExactNetRun(deltas,target){
  const first=new Map([[0,0]]);
  let sum=0,bestStart=-1,bestEnd=-1;
  for(let end=1;end<=deltas.length;end++){
    sum+=deltas[end-1];
    const start=first.get(sum-target);
    if(start!==undefined){
      const len=end-start, bestLen=bestEnd-bestStart;
      if(len>bestLen||(len===bestLen&&start<bestStart)){
        bestStart=start;bestEnd=end;
      }
    }
    if(!first.has(sum))first.set(sum,end);
  }
  return [bestStart,bestEnd];
}

module.exports = { longestExactNetRun };
