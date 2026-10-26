# Safest Maintenance Route — Reference Notes

## Recognition signals
"Distance to **nearest of many** sources" → **multi-source BFS** on an unweighted graph. "Choose a path maximizing its **minimum** vertex score" → **widest / maximum-bottleneck path**, not minimum-total-weight shortest path. This is a two-stage graph problem.

## Brute force → optimal
Naive first stage: BFS separately from each station to find its nearest hazard: O(n(n+m)). Naive second stage: enumerate simple start→goal paths and score each by its minimum safety; exponentially many paths can exist.

Optimal first stage: initialize a FIFO queue with **all hazard stations**, each at distance 0. BFS discovers the nearest-hazard hop count in O(n+m) time. Stations in components without hazards retain sentinel n (the largest possible finite hop distance in an n-vertex graph is n−1).

Optimal second stage: let `best[v]` be the greatest bottleneck safety discovered for any route from start to v. A route reaching u with score s and extending to v with station score d[v] has score `min(s, d[v])`. Improve `best[v]` when this exceeds its current value; prioritize the **largest** tentative bottleneck using `heapq` with negative priorities.

## Invariants and correctness
**BFS:** every vertex first discovered from the initial hazard frontier has its minimum number of edges to any hazard. No hazards in a component means all its vertices remain n.

**Heap phase:** every heap entry `(-score,u)` represents a discovered route to u with bottleneck score. `best[u]` is the maximum discovered score. Skip stale entries where the popped score differs from `best[u]`.

Why greedy settling works: extending a route can only **decrease or preserve** its bottleneck (min operation). Thus once the maximum-scored heap entry is popped, no route through a lower-scored unsettled frontier can improve it. The first non-stale pop of goal is optimal. This mirrors Dijkstra's label-setting proof, but with **max/min** instead of **min/plus**.

For the 6-station example, hazard 4 gives station scores: 4→0, 1→1, 5→1, 0→2, 3→2, 2→3. Route 0→2→3→5 has bottleneck min(2,3,2,1)=1; route 0→1→4→5 has bottleneck 0.

## Complexity
Building adjacency lists and multi-source BFS: O(n+m) time and O(n+m) space. Heap phase: O((n+m) log n) time for a simple graph and O(n+m) auxiliary space including the heap. Total O(n+m + (n+m) log n) time, O(n+m) space.

## Common mistakes
- Running BFS from one arbitrary hazard, missing closer hazards elsewhere.
- Treating an unreachable hazard as distance 0 or infinity; the **specified** safety score is n.
- Using `score + safety[v]` or maximizing a sum rather than `min(score,safety[v])`.
- Using a min-heap of scores, which settles the **least** safe route first.
- Marking a vertex visited on heap **push**; a better bottleneck may be discovered later.
- Returning -1 just because hazards are unreachable: that can make the route **maximally safe**, not impossible.
- Forgetting endpoint safety or the `start == goal` case.
- Confusing this max-bottleneck objective with an MST or ordinary shortest path.

## CS61B connections / Python recall
BFS, adjacency lists, and visited/distance arrays come directly from CS61B graph traversal. The heap phase uses the same **relaxation + stale-entry** pattern as Dijkstra, but changes the path algebra. Python `deque.popleft()` is O(1); a list `pop(0)` is O(n). `heapq` is a **min-heap**, so store negative scores for max-priority behavior. This is a spaced transfer of your earlier Dijkstra difficulty into a distinct graph optimization pattern.
