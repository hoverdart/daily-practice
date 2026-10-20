# Reference — Count the Fastest Dispatch Routes

## Recognition signals
You need a minimum **sum of positive edge weights** in a directed graph: use **Dijkstra** with a min-heap. The extra output (“how many optimal routes?”) is a **dynamic-programming count attached to shortest-path relaxation**, not a request to enumerate paths. This deliberately revisits the October 5 Dijkstra attempt (confidence 1/5) while introducing a new tie-handling invariant.

## Brute force versus optimal
Enumerating all simple routes can take exponential time in a branching graph. Running DFS and tracking the cheapest route plus a counter is infeasible for 100,000 vertices. An adjacency-list Dijkstra processes promising states in increasing tentative distance. Alongside `dist[v]`, maintain `ways[v]`, the number of minimum-cost routes to v found so far (mod 1e9+7).

For each directed edge u→v of weight w:
- **Strict improvement:** if `dist[u]+w < dist[v]`, replace `dist[v]` and set `ways[v] = ways[u]`. All older routes to v are too expensive.
- **Tie:** if `dist[u]+w == dist[v]`, add `ways[u]` to `ways[v]` modulo MOD. Each optimal route to u extends to a distinct optimal route to v along that edge.
- **Worse candidate:** do nothing.

Initialize `dist[0]=0, ways[0]=1` (one empty route). Other distances start at infinity, ways at zero. Use `long` for accumulated costs. Parallel edges are processed separately and intentionally contribute separately.

## Invariant and why positive weights matter
With **strictly positive** weights, any predecessor u on a shortest route to v has `dist[u] < dist[v]`. Dijkstra settles u **before** v. Therefore, by the time v is popped at its final distance, **all optimal incoming contributions have already been counted**. The ways count is final when v's outgoing edges are relaxed. This is why the tie case can update `ways[v]` without re-enqueuing v.

With **zero-weight edges**, equal-distance vertices may be popped in an order that misses later equal-cost contributions. This reference algorithm is deliberately scoped to **positive** weights; zero-cost edges require additional care (and zero cycles can make unrestricted walk counts ill-defined).

Stale heap entries are discarded with `if (poppedDistance != dist[u]) continue;`. This is the usual lazy decrease-key implementation.

## Complexity
Let n be vertices and m directed edges. Building adjacency lists is O(n+m). Every successful strict relaxation can insert a heap entry; there are O(m+1) such entries. Each heap operation costs O(log(m+1)), and each vertex's outgoing edges are scanned when its current best entry is popped. Total **O(n+m + m log(m+1))**, commonly written **O((n+m) log(n+m))**, and **O(n+m) auxiliary space** for adjacency lists, arrays, and heap. (With a standard binary heap, there can be O(m) stale entries.)

## Common mistakes
- Using BFS (counts edges, not weighted time) or Kruskal (connects the whole graph, not a source→target route).
- Using `int` for distances: a 100,000-edge path can exceed 32-bit limits.
- Resetting `ways[v]` to 1 on improvement instead of inheriting `ways[u]`.
- Forgetting to **add** on equal distances or to apply modulo.
- Treating parallel edges as one route despite the problem defining distinct **edge sequences**.
- Forgetting the empty route when `n=1`.
- Incorrect `PriorityQueue` comparator subtraction, e.g. `(int)(a[0]-b[0])`, which can overflow.
- Not skipping stale heap entries, causing repeated work.
- Applying this exact counting logic to zero/negative weights without reconsidering its invariant.

## Java syntax + CS61B connections
```java
List<List<int[]>> g = new ArrayList<>(n);
for (int i = 0; i < n; i++) g.add(new ArrayList<>());
g.get(u).add(new int[]{v, weight});

PriorityQueue<long[]> pq =
    new PriorityQueue<>((a,b) -> Long.compare(a[0], b[0]));
pq.add(new long[]{0L, 0L});
long[] state = pq.poll();
```

This ties together CS61B adjacency lists, min-heaps/priority queues, graph relaxation, Dijkstra's settled-distance invariant, and DP over a shortest-path dependency order. Contrast unweighted BFS (`O(n+m)`), Bellman-Ford (supports negative edges), and MST (different objective). The **distance strictly increases** along optimal edges here, which makes shortest-path counting a DAG-style dynamic program.
