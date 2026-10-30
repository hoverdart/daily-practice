"use strict";

/**
 * @param {number} n
 * @param {number[][]} edges - [from, to, score], DAG, may be negative
 * @param {number} start
 * @param {number} target
 * @returns {{maxWeight: number|null, ways: number}}
 */
function criticalRouteCount(n, edges, start, target) {
  // TODO:
  // 1. Build outgoing adjacency lists and indegrees.
  // 2. Kahn topological traversal (including unreachable vertices).
  // 3. DP best[u] = max path score from start; ways[u] = #max paths mod 1e9+7.
  // 4. For each u->v with weight w: replace on improvement, add on equality.
  // 5. Return null/0 if target is unreachable.
  throw new Error("TODO: implement criticalRouteCount");
}

module.exports = { criticalRouteCount };
