# Hard / Stretch — Hazard-Budget Courier

A courier travels on **directed** roads between `n` depots numbered `0..n-1`. Each road has a nonnegative travel time and a nonnegative hazard score. The courier starts at depot 0 and must reach depot `n-1` without the **sum of hazard scores exceeding `budget`**. Find the minimum total travel time, or -1 if no feasible route exists.

The graph may have cycles, parallel edges, and zero-time/zero-hazard roads. A fast route may be too hazardous; a slower one may be feasible.

## Required C API

    typedef struct { int from, to, time, risk; } Road;

    long long fastestSafeRoute(int n, int m, const Road *roads, int budget);

`roads` is an array of `m` directed edges; it may be NULL if `m == 0`. Do not change the input. Return a 64-bit answer (`long long`) because total time may exceed 32-bit `int`.

## Examples

- `n=3`, roads `[(0,2,1,4),(0,1,4,1),(1,2,2,1)]`: with budget 2, answer **6**; with budget 4, answer **1**.
- `n=2`, no roads: **-1**.
- `n=1`, no roads: **0**.
- `n=3`, roads `[(0,1,1,2),(1,2,1,2),(0,2,10,0)]`: budget 3 -> **10**, budget 4 -> **2**.

## Constraints and target

`1 <= n <= 200`, `0 <= m <= 3000`, `0 <= budget <= 30`, `0 <= time <= 10^9`, `0 <= risk <= 30`, valid endpoints. Target **O((nB + mB) log(mB+2))** time and **O(nB + mB)** space where `B=budget+1`.

Do not assume the best time to a physical depot is enough: arriving with different **hazard already spent** changes which future edges are legal. Implement the adjacency list and min-heap directly in C (no external heap library). Skip stale heap entries and free all allocated memory.

**CS61B connection:** Dijkstra relaxation, binary heaps/swim/sink, graph representation, state-space graphs, and C pointer/memory ownership.
