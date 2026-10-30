"use strict";

function closestSharedSupervisor(parent, a, b) {
  const ancestors = new Set();
  for (let x = a; x !== -1; x = parent[x]) ancestors.add(x);
  for (let x = b; x !== -1; x = parent[x]) {
    if (ancestors.has(x)) return x;
  }
  return -1;
}

module.exports = { closestSharedSupervisor };
