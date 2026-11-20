"use strict";
const assert=require("node:assert/strict");
const {sanitizeRoutingLog:solve}=require("./solution");

function oracle(s){
  let prefix="",balance=0;
  for(const c of s) {
    if(c==="("){balance++;prefix+=c;}
    else if(c===")"){if(balance){balance--;prefix+=c;}}
    else prefix+=c;
  }
  let answer="",closing=0;
  for(let i=prefix.length-1;i>=0;i--) {
    const c=prefix[i];
    if(c===")"){closing++;answer=c+answer;}
    else if(c==="("){if(closing){closing--;answer=c+answer;}}
    else answer=c+answer;
  }
  return answer;
}
const examples=[
  ["",""],["abc","abc"],[")(",""],["))((",""],["(a(b)","a(b)"],
  ["a)b(c)d(","ab(c)d"],["((x))","((x))"],["(a)b)c","(a)bc"],
  ["a((b)c","a(b)c"],["x(y)z","x(y)z"],["(()","()"],
  ["(((())))","(((())))"],["a(b)c)d(","a(b)cd"]
];
for(const [input,expected] of examples)assert.equal(solve(input),expected,input);
let seed=20261120;
function rand(k){seed ^= seed << 13;seed ^= seed >>> 17;seed ^= seed << 5;return (seed >>> 0)%k;}
for(let t=0;t<2500;t++){
  const s=Array.from({length:rand(70)},()=>["(",")","a","b","c"][rand(5)]).join("");
  assert.equal(solve(s),oracle(s),"oracle "+JSON.stringify(s));
}
const big="(".repeat(100000)+"a"+")".repeat(99999);
assert.equal(solve(big),"(".repeat(99999)+"a"+")".repeat(99999));
assert.equal(solve(")".repeat(100000)+"z"+"(".repeat(100000)),"z");
console.log("PASS easy: deterministic, independent two-pass oracle, large stress");

