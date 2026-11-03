# Reference Notes — Minimum Boot Stations for a One-Way Network

## Recognition signals
A **directed** network with propagation, reachability, cycles, and "minimum starting locations that can cover everything" points toward **strongly connected components (SCCs)** and their **condensation DAG**. Ordinary connected components are not enough: directed reachability is asymmetric. Also, vertices of indegree zero are not enough: an isolated directed cycle has no indegree-zero vertices but still requires a seed.

## Brute force versus optimal
For small n, enumerate subsets of starting stations in increasing size and run BFS/DFS from each subset until finding one that reaches all n. That is exponential in n. An alternative small-instance oracle computes all-pairs reachability and groups vertices with mutual reachability, which takes O(n³) with Floyd-Warshall.

Optimally:
1. Find SCCs using two DFS passes (Kosaraju). Record **finish times**, not discovery times, on the original graph.
2. Reverse every edge and traverse vertices in **descending finish order**. Each second-pass search identifies exactly one SCC.
3. Compute the smallest vertex label per SCC. For every original edge `u→v` with `scc[u] != scc[v]`, mark the destination SCC as having an incoming cross-SCC edge.
4. Choose the smallest representative of every SCC **without** incoming cross-SCC edges; sort the chosen representatives.

## Core invariants and proof
Within an SCC, every vertex can reach every other. Thus a single seeded vertex activates its entire SCC; the smallest label is the canonical choice. Contracting SCCs produces a DAG (if it had a directed cycle, those components would be mutually reachable and actually be one SCC).

**Necessity:** A source SCC in the condensation DAG has no incoming edges, so no boot outside it could activate it. At least one boot per source SCC is required.

**Sufficiency:** Every vertex in a finite DAG is reachable from some source vertex (follow incoming edges backward until reaching a source). Therefore booting every source SCC activates all SCCs. One boot per source is exactly optimal.

Kosaraju's first pass orders SCCs by graph DFS finishing times. Processing reversed graph in decreasing finish order prevents second-pass traversals from crossing into as-yet-unassigned SCCs. Marking a vertex as assigned **when pushing it** ensures each is pushed once. The iterative first pass uses a per-vertex next-neighbor cursor to preserve true postorder; simply popping a normal DFS stack would not.

## Complexity
Building outgoing/reversed adjacency lists is O(n+m). Both DFS passes and the cross-SCC scan take O(n+m). The final smallest-representative selection uses a boolean array indexed by station ID and a linear scan to output IDs in sorted order. This avoids comparison sorting, yielding **O(n+m) time and O(n+m) space** overall.

## Common mistakes
- Treating the graph as undirected or counting indegree-zero **vertices** instead of indegree-zero **SCCs**.
- Forgetting to build the reverse graph, or reversing just some edges.
- Collecting preorder instead of postorder in Kosaraju's first pass.
- Marking nodes only when they are popped and processing them repeatedly.
- Reaching a recursion-depth failure on a 120,000-vertex chain in Java. Prefer explicit stacks.
- Treating self-loops and parallel edges as multiple components.
- Counting internal SCC edges as incoming condensation edges.
- Forgetting the smallest-label selection and globally ascending output.

## CS61B connections
Graph DFS and postorder, adjacency lists, connectedness versus **strong** connectedness, reversed edges, condensation DAGs, and amortized O(V+E) traversal. This also contrasts with union-find: DSU can model undirected components but does **not** compute directed SCCs. Deep iterative DFS requires explicit per-frame progress (next-neighbor cursors), mirroring the recursive call stack.
