"use strict";

function cheapestRefundRoute(n, edges, start, target) {
  const reverse = Array.from({ length: n }, () => []);
  for (const [u, v] of edges) reverse[v].push(u);
  const canReach = new Uint8Array(n);
  const queue = [target];
  canReach[target] = 1;
  for (let head = 0; head < queue.length; head++) {
    for (const u of reverse[queue[head]]) {
      if (!canReach[u]) {
        canReach[u] = 1;
        queue.push(u);
      }
    }
  }
  if (!canReach[start]) return null;
  const usable = edges.filter(([u, v]) => canReach[u] && canReach[v]);
  const dist = Array(n).fill(Infinity);
  dist[start] = 0;
  for (let pass = 1; pass < queue.length; pass++) {
    let changed = false;
    for (const [u, v, w] of usable) {
      if (dist[u] === Infinity) continue;
      const candidate = dist[u] + w;
      if (candidate < dist[v]) {
        dist[v] = candidate;
        changed = true;
      }
    }
    if (!changed) return dist[target];
  }
  for (const [u, v, w] of usable) {
    if (dist[u] !== Infinity && dist[u] + w < dist[v]) return "UNBOUNDED";
  }
  return dist[target];
}

module.exports = { cheapestRefundRoute };
