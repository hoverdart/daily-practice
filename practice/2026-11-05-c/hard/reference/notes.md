# Mandatory Shortest-Route Edges — Recognition and Proof

## Recognition signals

The phrases **minimum number of hops** and **directed edges** imply BFS on an unweighted directed graph. The phrase **appears on every shortest route** is stronger than merely "lies on some shortest route"; counting all paths is an unattractive idea because the number of paths may be exponential.

The key abstraction is a shortest-path DAG made of edges that participate in some minimum-hop s-to-t route. Rather than constructing all routes, characterize each edge by distances and group it by BFS depth.

## Brute force, improvement, optimality

**Slow but correct oracle:** BFS once for D = shortest s-to-t distance. For every edge ID e, temporarily ignore it and BFS again. Edge e is mandatory iff the new distance is greater than D (including unreachable). Cost O(m(n+m)) time and O(n+m) space if each BFS uses adjacency lists. This is useful for randomized tests on tiny graphs.

**Optimal:** Run BFS from s on the original directed graph to get ds[u]. Run BFS from t on **reversed edges** to get dt[v], which is the shortest *original-direction* distance v->t. Let D=ds[t]. An edge e=(u->v) can appear in at least one shortest path precisely when ds[u] and dt[v] are finite and:

~~~text
ds[u] + 1 + dt[v] == D
~~~

For every eligible edge, increment count[ds[u]] and remember its edge ID. A layer k with count[k]==1 has one mandatory physical edge. Mark it. Scan IDs in original order to build a sorted result array.

## Why counting eligible edges by layer works

Every shortest s-to-t path has D edges. At each vertex on that path, its prefix length is exactly its BFS distance ds; otherwise a shorter path to the vertex followed by the remainder would yield an s-to-t walk shorter than D. Consequently the path uses exactly one edge from ds layer k to k+1 for each k = 0..D-1.

Every eligible edge lies on at least one s-to-t shortest path: take a shortest s->u path, that edge, and a shortest v->t path. Their lengths sum to D. A repeated vertex would allow a strictly shorter walk, so the concatenated length-D walk is a valid shortest route.

- If exactly one eligible edge crosses layer k, **all** shortest routes must use it.
- If two or more distinct eligible edges cross layer k, each can appear in a shortest route, and those routes cannot all use any one of them because each shortest route crosses the boundary only once.

This is about edge **IDs**. If two parallel edges have identical endpoints, each is a distinct alternative at the same layer; neither is mandatory. Self-loops cannot qualify because their hop cost is 1 and ds[u] is already no greater than ds[v].

## Complexity and data structures

Build two adjacency lists in C as arrays head[vertex] and next[edgeID]. Each edge is inserted once into forward and reverse lists. BFS visits each vertex at most once and scans each adjacency edge at most once: O(n+m) time. Filtering edges and scanning BFS layers costs O(n+m). Overall O(n+m) time and O(n+m) auxiliary space.

Two distances, one reusable BFS queue, two adjacency-list index arrays and layer counts are used. Result indices are allocated on the heap and owned by the caller.

## Frequent mistakes

- Using BFS from t on the *forward* graph, which computes distances t->v rather than v->t.
- Testing ds[u] + 1 + ds[v] rather than ds[u] + 1 + dt[v].
- Forgetting unreachable distances (-1), causing false positives.
- Counting endpoints instead of edge IDs, incorrectly marking a parallel edge compulsory.
- Confusing "edge on some shortest path" with "edge on all shortest paths".
- Treating a disconnected destination as having compulsory edges.
- Counting modulo a prime as proof of uniqueness (modular collisions can occur).
- Returning a pointer into temporary workspace after freeing it.

## CS61B connections

This brings together graph representations, BFS/queue invariants, parent/distance arrays, path length optimality, and directed graph reversal. It complements Dijkstra: when all edges have equal weight, BFS is sufficient and faster. The layer argument is a useful bridge toward shortest-path DAGs, dominators, and cut arguments, without needing to implement those more advanced tools.

