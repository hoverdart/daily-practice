# Reference Notes — Critical Relay Links

## Recognition signals
"Removing one edge increases the number of components" is a **bridge/cut-edge** problem, not a shortest-path or MST question. A DFS tree edge is a bridge only when its child subtree has no alternate connection to its parent or an ancestor.

## Brute force versus optimal
For each cable ID, remove it and recompute components by DFS/BFS: **O(m(n+m))** time and O(n+m) space. Discovery times and low-link values identify all bridges in **O(n+m)** total time.

## Core invariant / proof
- tin[u] is the unique discovery time of vertex u.
- low[u] is the minimum tin reachable from u's DFS subtree by descending tree edges and using at most one non-parent back edge, including staying at u.
- Initialize low[u]=tin[u]. For a previously discovered neighbor on a non-parent edge, minimize with tin[v]. After child v completes, minimize low[u] with low[v].
- Tree edge (u,v) is a bridge **iff low[v] > tin[u]**. Otherwise the subtree has an alternate edge reaching u or an ancestor; if greater, all routes out of v's subtree use (u,v).
- Parallel edges require skipping the **exact parent edge ID** rather than the parent vertex. The other cable provides a back edge. Self-loops never become bridges.

## Iterative DFS and complexity
Each vertex stores cursor[u], the next incident arc to inspect. The vertex stays on an explicit stack until all arcs are consumed. On pop, simulate recursive postorder: update its parent's low and test the parent edge. Start from every unvisited vertex to handle disconnected graphs. Scan bridge flags in input order to emit sorted IDs without sorting.

Adjacency arrays contain two directed arcs per undirected cable. Each vertex and arc is processed O(1) times: **O(n+m)** time, **O(n+m)** space. Iterative DFS avoids C call-stack overflow on long chains. Check allocations and free all arrays on every exit path.

## Common mistakes
- Starting only from vertex 0, or treating edges as directed.
- Skipping every edge to the parent vertex (wrong with parallel cables).
- Using >= instead of strict > for bridge detection.
- Updating parent low before a child has finished.
- Treating self-loops as bridges or assuming a connected input.
- Returning endpoint pairs rather than original edge IDs.
- Recursing 100,000 levels in C without considering stack limits.

## CS61B connections
DFS trees/back edges, adjacency lists, connected components, cycle detection, and postorder traversal. DSU handles online connectivity but does not directly identify every bridge in a static graph. Related extensions: articulation points (critical **vertices**) and 2-edge-connected components.
