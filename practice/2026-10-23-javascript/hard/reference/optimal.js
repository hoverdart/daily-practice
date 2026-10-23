"use strict";

// Binary min-heap of [distance, vertex, usedVoucher] triples.
class MinHeap {
  constructor() { this.a = []; }
  get size() { return this.a.length; }

  push(item) {
    const a = this.a;
    let i = a.length;
    a.push(item);
    while (i > 0) {
      const parent = (i - 1) >> 1;
      if (a[parent][0] <= item[0]) break;
      a[i] = a[parent];
      i = parent;
    }
    a[i] = item;
  }

  pop() {
    const a = this.a;
    const smallest = a[0];
    const last = a.pop();
    if (a.length > 0) {
      let i = 0;
      while (2 * i + 1 < a.length) {
        let child = 2 * i + 1;
        if (child + 1 < a.length && a[child + 1][0] < a[child][0])
          child++;
        if (a[child][0] >= last[0]) break;
        a[i] = a[child];
        i = child;
      }
      a[i] = last;
    }
    return smallest;
  }
}

function cheapestVoucherRoute(n, edges, start, goal) {
  const graph = Array.from({ length: n }, () => []);
  for (const [u, v, toll] of edges) graph[u].push([v, toll]);

  // Index 2*v is "voucher unused"; 2*v+1 is "voucher used".
  const dist = new Float64Array(2 * n);
  dist.fill(Infinity);
  dist[2 * start] = 0;

  const heap = new MinHeap();
  heap.push([0, start, 0]);

  while (heap.size > 0) {
    const [cost, u, used] = heap.pop();
    if (cost !== dist[2 * u + used]) continue; // stale entry
    if (u === goal && used === 1) return cost;

    for (const [v, toll] of graph[u]) {
      // Pay the road toll; voucher state remains unchanged.
      const next = 2 * v + used;
      const regularCost = cost + toll;
      if (regularCost < dist[next]) {
        dist[next] = regularCost;
        heap.push([regularCost, v, used]);
      }

      // Spend the voucher on this traversal: edge cost is zero.
      if (used === 0 && cost < dist[2 * v + 1]) {
        dist[2 * v + 1] = cost;
        heap.push([cost, v, 1]);
      }
    }
  }
  return -1;
}

module.exports = { cheapestVoucherRoute };

