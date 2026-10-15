# Hard / Stretch — Cheapest Route with Rebates

A delivery network has **directed** roads. A road may have a negative cost because of a rebate. Find the cheapest total cost from src to dst. Unlike Dijkstra problems, negative edges and negative cycles are allowed.

Return one of three statuses:

- -1: dst is unreachable from src.
- 0: a finite minimum cost exists; write it to *out.
- 1: some negative-cost cycle is reachable from src **and** can eventually reach dst; repeating that cycle makes the optimum unbounded below.

Do not change *out when returning -1 or 1.

Implement:

    typedef struct { int from, to, weight; } Edge;
    int cheapest_rebate_route(int n, const Edge *edges, int m,
                              int src, int dst, long long *out);

Example: 0→1 (5), 1→2 (-7), 0→2 (3) yields status 0 and cost -2 from 0 to 2. A reachable negative cycle leading to 2 instead yields status 1. A negative cycle in an isolated component, or one that cannot reach the destination, must not cause status 1.

Constraints: 1<=n<=200, 0<=m<=4000, vertex IDs 0..n-1, -1000000<=weight<=1000000, parallel edges and self-loops allowed. src, dst, and out are valid; edges may be NULL only if m==0. Allocate any arrays you need, and free them before returning.

**Target:** O(VE+V) time and O(V) auxiliary space. Avoid Dijkstra, whose greedy finalized-distance invariant fails with negative edges. This revisits graph relaxation while adding negative-cycle relevance and C memory ownership.
