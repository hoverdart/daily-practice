# Hard reference notes — Farthest Critical Server in a Tree

## Recognition signals

**Undirected tree**, **unique route**, **answer at every vertex**, **max distance to a marked node**, and **linear-time target** suggest **tree dynamic programming with rerooting**. Unlike a general weighted graph, a tree has exactly one route between any two nodes: no Dijkstra or relaxation is necessary. This is an extension of CS61B DFS/BFS, parent arrays, rooted trees, and traversal order. Because chain depth may be 120,000, avoid recursive DFS in Python.

## Brute force versus optimal

**Baseline:** For every critical server, run DFS/BFS over the tree, recording its distance to each vertex and updating a per-vertex maximum. Every traversal takes O(n) since there are n−1 edges; for c critical servers, **O(cn)** time, O(n) traversal space. If c=Θ(n), this is Θ(n²).

**Optimal:** Root the tree at 0, create an adjacency list and an **iterative** parent-before-child traversal order, then run two DP passes:

- **down[u]**: farthest distance from u to a critical vertex inside u's rooted subtree. Use −1 if none. In reverse traversal order, start with 0 if u itself is critical; for each child v with a reachable down[v], consider weight(u,v)+down[v].
- **up[u]**: farthest distance from u to any critical vertex **outside u's rooted subtree**, −1 if none. At root, up[0]=−1. To compute up[v] for child v, the best outside-v route through u can (a) lead into up[u], (b) stop at u if u is marked, or (c) lead into a *different* child subtree. Add weight(u,v) to the maximum of these candidates.

For option (c), retain the top two **(distance, source-child)** candidates at each u. The local marked node is its own distinct source −1. When processing child v, use the largest candidate unless its source is v, in which case use the second largest. Tied maxima must preserve distinct source identities; a tie should not invalidate the other branch.

The answer for u is max(down[u], up[u]) because every marked vertex is either in u's own rooted subtree or outside it.

## Formal invariants and correctness

Rooted-tree uniqueness makes the decomposition exact. The bottom-up invariant is: when processing u in reverse order, each child's down is correct because children occur after parents in the forward order. Any path from u to a marked descendant either has length 0 to u itself or first travels to exactly one child; maximizing the listed candidates is therefore complete.

The forward invariant is: before processing u, up[u] is the longest distance to any marked node outside u's subtree. A marked vertex outside child v's subtree falls into exactly one of the parent-side region, u itself, or a sibling subtree. The candidate computation enumerates all three without including v's own branch. Adding edge (u,v) yields the correct up[v]. Two best distinct sources suffice to maximize after excluding any single child, which makes the pass linear.

Finally, subtree and exterior form a disjoint partition of all critical vertices. If both are absent, −1 is correct. Otherwise the larger of the two distances is the farthest critical vertex.

## Complexity

An undirected tree has 2(n−1) adjacency-list entries. Build/parent order, down, and up each examine each vertex or adjacency item O(1) times. Scanning a vertex's children twice still sums to O(n) across the whole tree. Thus **O(n) time**, **O(n) auxiliary space** for adjacency, parent, order, mark set, down, up, and output. Nonnegative weights ensure all valid distances are ≥0, so −1 safely means 'no reachable marked node'. Python integer arithmetic handles path totals above 32-bit range.

## Common mistakes

- Include the child's own down[v] when computing its up[v]: this invents an invalid route that doubles back along the same edge.
- Keep only one best candidate, making it impossible to exclude that best child.
- Ignore a second candidate with **equal** distance; ties still need distinct sources.
- Use DFS recursion for a long chain and hit RecursionError.
- Assume a weighted tree needs Dijkstra or treat edges as directed.
- Confuse farthest marked *descendant* with farthest marked *anywhere*.
- Initialize up[root]=0: 0 represents a genuinely marked node, not an absent one.
- Treat zero weight as a missing path or overflow large sums in fixed-width languages.
- Rerun a traversal per node (accidental quadratic time), or mutate input edge lists.

## CS61B connections and extension

This is weighted adjacency-list traversal, tree parent/child structure, reverse/postorder aggregation, dynamic programming, and rerooting. Compare a graph shortest-path problem requiring Dijkstra due to multiple competing routes: a tree's unique paths remove that concern. Also contrast a plain subtree-DP problem (answers for the root only) with an all-nodes task, where outside-subtree state is essential.

**Optional alternate insight:** For nonnegative weighted trees, pick any critical node, find the farthest critical A; from A find a farthest critical B. A and B are marked-diameter endpoints. The eccentricity of each node with respect to the marked set equals max(dist(node,A), dist(node,B)). This yields another linear algorithm with several iterative traversals; proving the tree-diameter endpoint property is a worthwhile follow-up stretch.
