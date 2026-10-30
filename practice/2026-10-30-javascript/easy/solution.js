"use strict";

/**
 * @param {number[]} parent - rooted forest; -1 marks a root
 * @param {number} a
 * @param {number} b
 * @returns {number} lowest common ancestor, or -1
 */
function closestSharedSupervisor(parent, a, b) {
  // TODO: store ancestors of a (including a); climb b toward its root.
  // Never recurse down the tree: height can be 200,000.
  throw new Error("TODO: implement closestSharedSupervisor");
}

module.exports = { closestSharedSupervisor };
