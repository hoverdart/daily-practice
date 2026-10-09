# Hard / Stretch — Hop-Limited Resilient Route

An undirected network has `n` stations numbered `0..n-1`. Each cable `[u,v,delay]` has a **nonnegative integer delay**. A route's **peak delay** is the largest cable delay along that route (not the sum). Find the **minimum possible peak delay** from `source` to `target` using **at most `maxHops` cables**. Return `-1` if no such route exists.

Implement:

```js
function minimumPeakDelay(n, edges, maxHops, source, target) { /* ... */ }
```

Examples:
- `n=5, edges=[[0,1,7],[1,4,4],[0,2,2],[2,3,3],[3,4,3]]`, `source=0,target=4`:
  - `maxHops=2` → `7` (path `0→1→4`).
  - `maxHops=3` → `3` (path `0→2→3→4`).
- `n=3, edges=[[0,2,9],[0,1,2],[1,2,2]]`, `maxHops=1` → `9`; with `maxHops=2` → `2`.
- `source===target` → `0`, even with zero hops.
- No qualifying route → `-1`.

Constraints: `1<=n<=200000`; `0<=edges.length<=200000`; `0<=delay<=10^9`; `0<=maxHops<=200000`; valid vertex IDs. Parallel cables and self-loops may appear. Do not mutate inputs.

**Target:** `O((V+E) log(W+1))` time and `O(V+E)` space, where `W` is the largest delay. (At most ~30–31 threshold checks for the stated delay range.)

**Before coding:** Why is ordinary shortest-sum Dijkstra the wrong objective? Why is “a path of at most K hops using only edges with delay <= T exists” a monotone yes/no predicate?

**CS61B:** graph adjacency lists, BFS shortest hop counts, binary search on answer, monotone feasibility predicates, and queue invariants.