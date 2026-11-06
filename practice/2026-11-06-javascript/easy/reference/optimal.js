"use strict";

function closestBlockingBeacon(strengths) {
  const answer = new Array(strengths.length).fill(-1);
  const stack = [];
  for (let i = 0; i < strengths.length; i++) {
    while (stack.length && strengths[stack[stack.length - 1]] < strengths[i]) {
      stack.pop();
    }
    if (stack.length) answer[i] = stack[stack.length - 1];
    stack.push(i);
  }
  return answer;
}

module.exports = { closestBlockingBeacon };
