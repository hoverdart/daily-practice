"use strict";

function longestRecalibratableRun(codes, k) {
  const freq = new Map();
  let left=0, maxFreq=0, best=0;
  for(let right=0;right<codes.length;right++) {
    const x=codes[right];
    const newCount=(freq.get(x)||0)+1;
    freq.set(x,newCount);
    maxFreq=Math.max(maxFreq,newCount);
    while(right-left+1-maxFreq>k) {
      const y=codes[left++];
      const remaining=freq.get(y)-1;
      if(remaining===0) freq.delete(y);
      else freq.set(y,remaining);
      // maxFreq intentionally NOT decreased.
    }
    best=Math.max(best,right-left+1);
  }
  return best;
}

module.exports = { longestRecalibratableRun };
