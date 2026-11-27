"use strict";

function calibrationNeighbors(root, target) {
  let lower = null, upper = null;
  let node = root;
  while (node !== null) {
    if (node.key === target) return [target, target];
    if (node.key < target) {
      lower = node.key;
      node = node.right;
    } else {
      upper = node.key;
      node = node.left;
    }
  }
  return [lower, upper];
}

module.exports = { calibrationNeighbors };
