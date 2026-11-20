"use strict";

function shortestEvidenceWindow(codes, required) {
  if (required.length===0) return [0,0];
  const need=new Map();
  for(const x of required) need.set(x,(need.get(x)??0)+1);
  let have=new Map(), missing=required.length, left=0, bestStart=-1, bestEnd=-1;
  for(let right=0;right<codes.length;right++) {
    const x=codes[right];
    if(x==="#") { have.clear(); missing=required.length; left=right+1; continue; }
    if(need.has(x)) {
      const old=have.get(x)??0;
      have.set(x,old+1);
      if(old<need.get(x)) missing--;
    }
    while(missing===0) {
      if(bestStart<0 || right+1-left<bestEnd-bestStart) {
        bestStart=left; bestEnd=right+1;
      }
      const first=codes[left++];
      if(need.has(first)) {
        const old=have.get(first);
        have.set(first,old-1);
        if(old<=need.get(first)) missing++;
      }
    }
  }
  return [bestStart,bestEnd];
}

module.exports = { shortestEvidenceWindow };
