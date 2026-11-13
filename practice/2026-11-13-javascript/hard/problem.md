# Hard / stretch — Alternating-Band Relay Route

## Scenario

A directed network contains stations `0..n-1`. Each directed link is `[from,to,delay,band]`, with a nonnegative integer `delay` and a band `0` or `1`. For interference control, a valid route must use **alternating bands**: consecutive links may not use the same band. The **first link can use either band**. Stations or edges may be revisited.

Return minimum total delay from `source` to `target`, or `-1` if no legal route exists. If source equals target, zero-link route costs 0.

```js
function minimumAlternatingRoute(n, edges, source, target) { /* number */ }
```

**Limits:** `1 <= n <= 100000`, `0 <= edges.length <= 200000`, `0 <= delay <= 1000000`, valid IDs and band in {0,1}. Parallel links, directed cycles, zero-delay edges, and self-links are allowed. Total finite distances are exactly representable by `Number`. Do not mutate input.

## Examples

```js
minimumAlternatingRoute(3, [[0,1,4,0],[1,2,9,0]], 0, 2) // -1
minimumAlternatingRoute(3, [[0,1,4,0],[1,2,9,1]], 0, 2) // 13
minimumAlternatingRoute(4,
 [[0,1,1,0],[1,3,1,0],[0,2,4,0],[2,1,1,1]], 0, 3) // 6
```

Why is one `dist[node]` insufficient? Model state as `(node,lastBand)`. Describe a Bellman-Ford baseline on the expanded graph, then use Dijkstra with a **hand-written JavaScript binary min-heap**. Explain why nonnegative delays matter. Target **O((n+m)log(n+m)) time**, **O(n+m) space**.
