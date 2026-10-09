"use strict";
function firstCapacityIndex(loads,limit) {
  let lo=0, hi=loads.length;
  while(lo<hi){
    const mid=lo+Math.floor((hi-lo)/2);
    if(loads[mid]>=limit) hi=mid;
    else lo=mid+1;
  }
  return lo===loads.length ? -1 : lo;
}
module.exports = { firstCapacityIndex };
