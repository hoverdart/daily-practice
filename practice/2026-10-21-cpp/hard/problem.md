# Hard / Stretch — Second Distinct Transit Cost

A delivery network is a **directed** graph with n stations numbered 0..n−1. Each edge (u,v,w) has a **strictly positive** integer travel cost w. A route is a **walk**: it may revisit stations and traverse edges multiple times. Two walks with the same total cost count as the **same cost**, even if their sequences differ.

Given source s and target t, return the **second-smallest DISTINCT total cost** among all s→t walks. Return -1 if fewer than two distinct costs exist. If s=t, the empty walk of cost 0 is allowed, so the answer is the cheapest **positive-cost** closed walk from s to itself (if any).

```cpp
struct Edge { int from, to; long long cost; };
long long secondDistinctTransitCost(
    int n, const std::vector<Edge>& edges, int source, int target);
```

Examples:
- edges [(0,1,2),(0,1,4),(1,2,3)], s=0,t=2 → 7 (costs 5,7).
- edges [(0,1,2),(0,1,2),(1,2,3)], s=0,t=2 → -1 (only cost 5).
- edges [(0,1,7),(1,0,4)], s=0,t=1 → 18 (7 then 7+4+7).
- edges [(0,1,7),(1,0,4)], s=0,t=0 → 11 (empty walk cost 0, then cycle cost 11).
- no s→t walk → -1.

**Constraints:** 1 ≤ n ≤ 150,000; 0 ≤ m ≤ 250,000; valid vertex indices; 1 ≤ w ≤ 1,000,000,000; parallel edges and self-loops allowed. The answer fits in signed 64-bit. Target O((n+m) log(n+m)) time and O(n+m) space.

Explain why ordinary Dijkstra storing only one distance per station is insufficient, why equal-cost routes do not create a second answer, why positive weights matter, and how to use a min-heap and *two distinct best distances per vertex*. **Do not** enumerate all walks.
