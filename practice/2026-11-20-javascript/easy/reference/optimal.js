"use strict";

function sanitizeRoutingLog(text) {
  const bad = new Uint8Array(text.length);
  const stack = [];
  for (let i=0;i<text.length;i++) {
    if (text[i] === "(") stack.push(i);
    else if (text[i] === ")") {
      if (stack.length) stack.pop();
      else bad[i] = 1;
    }
  }
  for (const i of stack) bad[i] = 1;
  const result=[];
  for(let i=0;i<text.length;i++) if(!bad[i]) result.push(text[i]);
  return result.join("");
}

module.exports = { sanitizeRoutingLog };
