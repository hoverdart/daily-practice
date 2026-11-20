"use strict";
const assert=require("node:assert/strict");
const {shortestEvidenceWindow:solve}=require("./solution");

function oracle(codes,required){
  if(required.length===0)return [0,0];
  const need=new Map();
  for(const x of required)need.set(x,(need.get(x)||0)+1);
  let best=[-1,-1];
  for(let l=0;l<codes.length;l++){
    const count=new Map();
    for(let r=l;r<codes.length;r++){
      if(codes[r]==="#")break;
      count.set(codes[r],(count.get(codes[r])||0)+1);
      let ok=true;
      for(const [x,k] of need)if((count.get(x)||0)<k){ok=false;break;}
      if(ok&&(best[0]<0||r+1-l<best[1]-best[0]))best=[l,r+1];
    }
  }
  return best;
}
const cases=[
  [[],[],[0,0]],[[],["a"],[-1,-1]],[["a"],[],[0,0]],
  [["a","b"],["a","b"],[0,2]],[["a","b","a","b"],["a","b"],[0,2]],
  [["a","a","#","b","a","b","a"],["a","b","a"],[4,7]],
  [["a","#","b"],["a","b"],[-1,-1]],
  [["auth","misc","auth","db","reset","auth","db"],["auth","auth","db"],[0,4]],
  [["a","a","a"],["a","a"],[0,2]],
  [["a","#","a","a"],["a","a"],[2,4]],
  [["a","x","b","#","b","a"],["a","b"],[4,6]],
  [["x","y","y","x","y"],["x","y","y"],[0,3]],
  [["#","#"],["x"],[-1,-1]]
];
for(const [codes,req,expected] of cases){
  const original=codes.slice(),oldReq=req.slice();
  assert.deepEqual(solve(codes,req),expected,JSON.stringify({codes,req}));
  assert.deepEqual(codes,original);assert.deepEqual(req,oldReq);
}
let seed=20261120;
function rand(k){seed ^= seed << 13;seed ^= seed >>> 17;seed ^= seed << 5;return (seed >>> 0)%k;}
for(let t=0;t<1800;t++){
  const codes=Array.from({length:rand(25)},()=>["a","b","c","d","z","#"][rand(6)]);
  const req=Array.from({length:rand(7)},()=>["a","b","c"][rand(3)]);
  assert.deepEqual(solve(codes,req),oracle(codes,req),JSON.stringify({codes,req}));
}
const n=180000;
assert.deepEqual(solve(Array(n-1).fill("a").concat("b"),["a","a","b"]),[n-3,n]);
assert.deepEqual(solve(Array.from({length:n},(_,i)=>i%2?"#":"a"),["a","a"]),[-1,-1]);
console.log("PASS medium: deterministic, independent quadratic oracle, large stress");

