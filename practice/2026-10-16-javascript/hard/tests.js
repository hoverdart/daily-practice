"use strict";
const assert = require("node:assert/strict");
const { shortestKeycardEscape } = require("./solution");
function oracle(grid) {
  // Independent O(states^2) shortest-path oracle for tiny random mazes.
  const R=grid.length,C=grid[0].length,N=R*C*16;
  let start=0;
  for(let r=0;r<R;r++)for(let c=0;c<C;c++)if(grid[r][c]==="S")start=r*C+c;
  const d=Array(N).fill(Infinity),done=Array(N).fill(false);
  d[start*16]=0;
  for(let t=0;t<N;t++){
    let s=-1;
    for(let i=0;i<N;i++)if(!done[i]&&(s<0||d[i]<d[s]))s=i;
    if(s<0||d[s]===Infinity)break;
    done[s]=true;
    const mask=s%16,pos=Math.floor(s/16),r=Math.floor(pos/C),c=pos%C;
    if(grid[r][c]==="E")return d[s];
    for(const [dr,dc] of [[0,1],[0,-1],[1,0],[-1,0]]){
      const nr=r+dr,nc=c+dc;
      if(nr<0||nr>=R||nc<0||nc>=C)continue;
      const ch=grid[nr][nc];
      if(ch==="#")continue;
      if(ch>="A"&&ch<="D"&&!(mask&(1<<(ch.charCodeAt(0)-65))))continue;
      const nm=ch>="a"&&ch<="d"?mask|(1<<(ch.charCodeAt(0)-97)):mask;
      const v=(nr*C+nc)*16+nm;
      d[v]=Math.min(d[v],d[s]+1);
    }
  }
  return -1;
}
const fixed=[
  [["SE"],1], [["SAE"],-1], [["#a##","S.AE","####"],5],
  [["S#E"],-1], [["S.",".E"],2],
  [["S.a","##A","..E"],4],
  [["S..","###","..E"],-1]
];
for(const [grid,want] of fixed) assert.equal(shortestKeycardEscape(grid),want,JSON.stringify(grid));
let seed=20261016;
const rnd=()=>{seed=(Math.imul(seed,1664525)+1013904223)>>>0;return seed/4294967296;};
const ri=n=>Math.floor(rnd()*n);
for(let t=0;t<250;t++){
  const R=2+ri(3),C=2+ri(3),symbols=[".",".",".","#","a","b","A","B"];
  const g=Array.from({length:R},()=>Array.from({length:C},()=>symbols[ri(symbols.length)]));
  g[0][0]="S";g[R-1][C-1]="E";
  const grid=g.map(row=>row.join(""));
  assert.equal(shortestKeycardEscape(grid),oracle(grid),JSON.stringify(grid));
}
const big=["S"+".".repeat(29),...Array.from({length:28},()=> ".".repeat(30)), ".".repeat(29)+"E"];
assert.equal(shortestKeycardEscape(big),58);
console.log("PASS hard: fixed, 250 seeded independent shortest-path oracle cases, 30x30 stress");
