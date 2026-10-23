# Explanation — Single-Use Transit Voucher

## Recognition signals
A weighted directed network with **nonnegative** edge costs suggests Dijkstra. But "one coupon / one wall break / one free transition" is a signal to **expand the state**: location alone does not determine future choices. This is a shortest-path problem on a product graph.

## Brute force versus optimal
**Brute force:** enumerate all possible walks and choose a road to waive. Cycles make this unsuitable without pruning.

**Alternative polynomial solution:** compute ordinary shortest paths from start and to goal (reverse edges), then evaluate each edge (u,v,w) as the free edge: distStart[u] + distToGoal[v]. This gives a strong O((n+m) log(n+m)) approach too, provided a valid walk using an edge exists. It is a good independent way to reason about the answer.

**Chosen optimal solution:** run Dijkstra once over **2n states**. State (v,0) means at vertex v with voucher unused; (v,1) means used. Every original edge u→v with toll w creates:
- (u,0)→(v,0) with cost w;
- (u,0)→(v,1) with cost **0**;
- (u,1)→(v,1) with cost w.

The target is (goal,1), never (goal,0). This enforces **exactly once**, not at most once.

## Invariant and proof sketch
dist[2*v+used] is the best discovered toll for that complete state. Heap entries are tentative candidates; skip entries whose cost differs from the current best. Every expanded edge has cost >= 0, including voucher transitions of cost 0, so the standard Dijkstra invariant holds: when a non-stale state is popped, its distance is final. The first finalized (goal,1) is therefore the minimum valid cost.

**Start equals goal:** the zero-edge walk ends in (goal,0) and does not qualify. A directed cycle (including a self-loop) can use the voucher and return; without such a walk, return -1.

## Complexity
The expanded graph has **2n vertices and at most 3m directed transitions**. Building adjacency lists takes O(n+m). With a binary min-heap and lazy stale entries, time is **O((n+m) log(n+m))** and space **O(n+m)** for adjacency lists, distances, and heap. For n=1 and m=0, no valid route exists.

## Common mistakes
- A single visited[v] or dist[v] merges states with different voucher availability.
- Returning as soon as goal is reached **before** the voucher is spent.
- Treating roads as undirected.
- Using a FIFO queue for arbitrary weighted edges.
- Marking a vertex visited on insertion instead of finalization.
- Forgetting the **free** transition when used=0 or allowing it after used=1.
- Repeatedly sorting an array instead of using a heap; this breaks the target bound.
- Overlooking start===goal, self-loops, parallel roads, and unreachable destinations.
- Assuming zero-weight edges invalidate Dijkstra: **negative** edges do, zero edges do not.

## CS61B connections
This synthesizes **graph adjacency lists**, **Dijkstra relaxation**, and **priority queues / binary heaps**. The two-layer construction is the same principle behind state-space BFS for keycards or remaining obstacle removals, but weights require a min-heap. In Java, use PriorityQueue; in C++, priority_queue with greater; in JavaScript, implement a heap explicitly.

