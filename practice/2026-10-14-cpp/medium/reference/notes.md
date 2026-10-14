# Reference notes — Fewest Road Reversals

## Recognition signals

This is **minimum total cost along a route**, not minimum hops (plain BFS) or connect-all-minimum-cost (MST). Every transition costs exactly **0 or 1**, so use **0–1 BFS** with a deque, a special case of nonnegative shortest paths.

## Modeling and brute force

For each recorded (u,v), add directed arcs (u→v,0) and (v→u,1). Enumerating every route can take exponential time. Standard Dijkstra with a binary heap is correct but O((n+m)log n). The binary costs let 0–1 BFS remove the heap factor.

## Algorithm and invariant

Set dist[source]=0 and all others infinity; enqueue source at front. For an edge u→v of cost w, if dist[u]+w improves dist[v], update and push **front** for w=0, **back** for w=1. Store (distance snapshot, vertex) to skip stale deque entries. The deque handles states in nondecreasing tentative-distance layers: cost-0 edges remain in the current layer, cost-1 edges enter the next. Relaxation therefore finds optimal reversal counts.

## Complexity

Build adjacency in O(n+m) time/space (2m directed arcs). 0–1 BFS uses O(n+m) time and O(n+m) total space including graph and deque. Distances are at most n−1 on a simple optimal path, so int is sufficient.

## Common mistakes

- Forget the backward arc or give it the wrong weight.
- Use FIFO BFS, which minimizes hops rather than reversals.
- Mark visited once on insertion and forbid distance improvements.
- Push both weights to the back, losing ordering.
- Forget source==target, disconnected graphs, parallel edges, or self-loops.
- Use Dijkstra with a heap unnecessarily (correct, but misses target complexity).

## CS61B / C++ connection

This combines adjacency lists, BFS queues, deque operations, and Dijkstra's edge **relaxation**. std::deque supports efficient push/pop at either end. vector<vector<pair<int,int>>> stores (neighbor, weight); C++17 auto [v,w] unpacks pairs. For arbitrary nonnegative weights use Dijkstra; for uniform weights use ordinary BFS.
