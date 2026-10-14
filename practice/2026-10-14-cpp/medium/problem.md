# Medium — Fewest Road Reversals

A facility's delivery network has n junctions (0 through n−1) and directed one-way roads (u,v). Driving in the recorded direction costs **0**; traversing the same road backward requires a temporary reversal costing **1**. Find the minimum number of reversed traversals along a route from source to target. Return −1 if the target is disconnected even when reversals are allowed.

```cpp
int minRoadReversals(int n,
    const std::vector<std::pair<int,int>>& roads,
    int source, int target);
```

Examples:
- n=4, roads [(0,1),(2,1),(2,3)], source=0, target=3 → 1.
- n=3, roads [(1,0),(2,1)], source=0, target=2 → 2.
- n=5, roads [(0,1),(2,3)], source=0, target=3 → −1.
- source == target → 0.

Constraints: 1 ≤ n ≤ 200000; 0 ≤ roads.size() ≤ 300000; valid indices; parallel roads and self-loops permitted.

Target: **O(n+m) time and space**. Why does the 0/1 edge-weight restriction permit a deque instead of Dijkstra's binary heap? Why is ordinary FIFO BFS incorrect?
