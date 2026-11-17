# Reference notes — Safest Bottleneck Route Queries

## Recognition signals

The cost of a path is its **largest edge**, not the sum of its edges. This is a *minimax* (bottleneck) objective. For one source/target, a modified Dijkstra uses relaxation candidate = max(currentCost, edgeWeight). For **many** queries on an undirected, static graph, the useful non-obvious fact is that a **minimum spanning forest** preserves the minimum bottleneck between every connected pair.

## Baseline versus optimized approach

**Baseline:** run a minimax Dijkstra for each query, with dist[source] = 0 and relax to max(dist[u], w). This handles nonnegative weights (indeed the max rule is monotone) and disconnected targets, but repeated q times costs approximately O(q(m+n) log n) with a binary heap. For 200k queries it is too slow.

**Optimal:**

1. Sort edges by ascending exposure. Run Kruskal with union-find (path compression and union by size). Every accepted edge joins different DSU components. The result is a minimum spanning **forest**.
2. Iteratively BFS (or DFS) each tree. Store component ID, depth, immediate parent up[0][node], and exposure maxOnJump[0][node] of the edge to parent.
3. Build binary-lifting tables: up[k][v] is the ancestor 2^k steps above v, and maxOnJump[k][v] is the maximum edge on that upward segment. Formula: up[k][v] = up[k-1][up[k-1][v]], and maxOnJump[k][v] = max(maxOnJump[k-1][v], maxOnJump[k-1][up[k-1][v]]).
4. For each query, return 0 for equal endpoints, -1 for different components, otherwise raise the deeper node until depths match and then raise both nodes until their parents meet. Aggregate the maximum of every traversed edge, including the last edges into LCA.

## Why an MST path is minimax: exchange/cut proof

Consider the unique u–v path in a chosen MST and one of its maximum-weight edges e, of weight W. Deleting e cuts the tree into two sides containing u and v respectively. If there were a u–v route whose **every** edge was strictly lighter than W, that route must cross this cut using some edge f with weight < W. Replacing e with f would reconnect the tree with smaller total weight, contradicting its minimum-spanning property. Thus every u–v route has a bottleneck at least W, while the MST path achieves W. The same argument applies component-wise to a minimum spanning forest. Equal-weight ties do not break the property.

This proof is different from claiming MST paths minimize sums; they generally do **not**.

## Correctness and runtime

Kruskal accepts exactly edges connecting currently disjoint components, and because of the sorted order produces an MSF. BFS roots each tree and records exact parent/depth values. Inductively, a 2^k jump's max table contains the maximum edge on that entire upward segment. Binary lifting partitions the tree path into such segments (plus the final two LCA edges), so its maximum is exactly the unique forest-path bottleneck, and the theorem above proves global optimality.

Time: O(m log m) sorting, O(m alpha(n)) union-find, O(n log n) lifting preprocess, and O(q log n) queries, altogether O(m log m + (n+q) log n) up to the union-find term. Space: O(m) forest representation + O(n log n) lift tables + O(n) DSU/traversal; the q-element result uses O(q) output space. On graph families with m=0, understand sorting work as zero. The algorithm is nonrecursive to avoid stack overflow.

## Copyable Java snippets

~~~java
// Kruskal sorting without modifying the input rows:
int[][] ordered = edges.clone();
Arrays.sort(ordered, (x, y) -> Integer.compare(x[2], y[2]));

// Binary lift through the set bits of an integer gap:
for (int k = 0; k < LOG; k++) {
    if (((gap >>> k) & 1) != 0) {
        answer = Math.max(answer, maxOnJump[k][u]);
        u = up[k][u];
    }
}
~~~

## Common mistakes

- Running shortest-sum Dijkstra or unweighted BFS; neither optimizes a maximum edge.
- Building a spanning tree **without** choosing minimum edges.
- Answering 0 for unreachable nodes; the required sentinel is -1.
- Using the DSU parent pointers as though they were MST parent pointers. DSU parents encode *sets*, not actual graph paths.
- Omitting the two final edges when both lifted nodes become children of LCA.
- Mishandling depth differences, roots, same-vertex queries, or multiple components.
- Incorrectly assuming all MST edge weights are positive; zero is allowed, so 0 is the neutral maximum.
- Sorting edges in place and mutating caller input.
- Recursing on a 100k-node path in Java.
- Using path length or sum instead of maximum for the maxOnJump aggregator.

## CS61B connections

Kruskal, greedy cut/exchange reasoning, weighted quick union and path compression, adjacency lists, BFS/DFS traversal, rooted trees, binary lifting (ancestor preprocessing), and maximum-on-path aggregation. Graph questions with *many static bottleneck queries* may be transformed into tree queries rather than answered with Dijkstra repeatedly.

