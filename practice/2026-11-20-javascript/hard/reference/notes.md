# Reference notes — Cheapest Route After Reversing One Link

## Recognition signals

A directed weighted graph with nonnegative weights suggests **Dijkstra**. The phrase "reverse at most one edge" is the critical extension: enumerate the location of the one special operation, but **reuse** shortest-path information rather than rerun a search for every edge.

## Brute force vs optimal

- **Brute force:** for each of E directed edges, physically reverse it, run Dijkstra from s to t, restore it, and keep the best; roughly O(E·(V+E)log V). Include the unchanged graph.
- **Optimal:** run Dijkstra *once* from s in the original directed graph, obtaining `from[x]`. Run Dijkstra *once* from t in the reverse graph, obtaining `toTarget[x]` (which equals the original shortest x→t distance). For each original edge `u -> v` with weight `w`, flipping that edge yields the candidate `from[v] + w + toTarget[u]` if both pieces are reachable. Compare with `from[target]`, representing no reversal.

## Correctness reasoning

Any route using one reversed link has an original-edge prefix ending at v, the flipped traversal v→u, and an original-edge suffix from u to t. The prefix and suffix cost at least `from[v]` and `toTarget[u]`, respectively; therefore the candidate is a lower bound on that route. Conversely, concatenating shortest original-edge prefix, flipped edge, and shortest suffix constructs a valid walk with no more than one reversed edge. If that walk repeats a vertex, nonnegative weights let us eliminate a cycle without increasing cost. Thus the candidate is attainable or improvable by a valid route. Considering all flipped edges and the zero-flip route gives the optimum.

The reverse graph is constructed solely for computing distances *toward* t; it does NOT make the actual package network bidirectional.

## Complexity

Build adjacencies in O(V+E) time and space. Two binary-heap Dijkstra passes cost O((V+E)log V) using lazy insertions, and the final E-edge pass is O(E). Distances and adjacency lists use O(V+E) memory, and each heap has O(E+V) pending items in the worst case. Node count and cost bounds permit ordinary JavaScript Number arithmetic without precision loss.

## Dijkstra/heap invariant

At extraction of a non-stale minimum candidate `d[u]`, there is no strictly shorter path to u still undiscovered: nonnegative edge weights would force a predecessor with a smaller tentative distance to be popped first. Relax every outgoing edge with `if (d+w < dist[v])`, and ignore old heap entries with `if (d !== dist[u]) continue`.

## Common mistakes

- Using BFS when costs are not all equal.
- Assuming `from[u] + w + toTarget[v]` corresponds to reversing `u -> v`; that formula is for traveling it *forward*.
- Computing the second Dijkstra on the original graph from t instead of the reversed graph.
- Counting the same edge twice or making **all** links bidirectional.
- Missing the no-flip answer or unreachable distances.
- Incorrect min-heap pop/sift-down when the heap becomes empty or has only one child.
- Reversing an edge of negative weight without changing the algorithm (Dijkstra would be invalid).

## CS61B connections

Adjacency lists, relaxation, binary heaps/PQs and the edge-direction distinction come directly from CS61B graph algorithms. This problem introduces a powerful interview transfer pattern: **precompute distances from the start and toward the goal, then splice in one exceptional transition**. Compare it with expanded-state Dijkstra (tracking whether the reversal has been used); both are valid, but the two-pass reduction is simpler here.

