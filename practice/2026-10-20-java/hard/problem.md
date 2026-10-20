# Hard / Stretch — Count the Fastest Dispatch Routes

A directed transportation network contains `n` stations numbered `0..n-1`. Every directed edge `[from, to, travelTime]` has a **strictly positive** integer travel time. You must dispatch from station `0` to station `n-1`.

Return a two-element `long[]`:

1. The **minimum total travel time** from `0` to `n-1`.
2. The **number of distinct minimum-time routes**, modulo `1_000_000_007`.

Two routes are distinct if they use different **sequences of edges**. Parallel edges are permitted and count as different choices. If the destination is unreachable, return `[-1, 0]`. If `n=1`, the empty route from station 0 to itself has cost 0 and counts as **one** route.

Implement:

```java
public static long[] fastestRouteAndCount(int n, int[][] edges)
```

Examples:
- `n=4`, edges `[[0,1,1],[0,2,1],[1,3,1],[2,3,1]]` → `[2,2]`.
- `n=3`, edges `[[0,1,1],[0,1,1],[1,2,1]]` → `[2,2]` (parallel edges).
- `n=3`, edges `[[0,1,5]]` → `[-1,0]`.

Constraints: `1 <= n <= 100_000`, `0 <= edges.length <= 200_000`, `0 <= from,to < n`, `1 <= travelTime <= 1_000_000_000`. Directed self-loops and parallel edges may appear. Do not mutate the input.

**Target:** O((n+m) log(n+m)) time and O(n+m) space with an adjacency list and a min-priority queue. Distances must be `long`, not `int`.

Reasoning prompts:
- What does an ordinary BFS fail to account for?
- How does the relaxation step differ when a new route is **shorter** versus **equally short**?
- Why does **strictly positive** edge weight matter when counting routes during Dijkstra's algorithm?