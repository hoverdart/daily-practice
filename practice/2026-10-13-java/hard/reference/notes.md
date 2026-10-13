# Reference notes — Prelinked Fiber Network

## Recognition signals: MST versus shortest path

The objective is to connect **every vertex** at minimum **total selected-edge cost**. That is a minimum spanning tree (MST) / minimum spanning forest completion problem, **not** a shortest path from one station. Dijkstra minimizes a path cost from a source; Kruskal minimizes the sum of edges required for global connectivity. The preinstalled links form zero-cost connectivity that should be contracted conceptually before buying edges.

## Brute force versus optimal

Enumerating all subsets of E candidate edges, checking connectivity, and selecting the cheapest costs roughly O(2^E (n+E)) and is impossible for large E. The tests use exactly this independent oracle on tiny random graphs.

Kruskal's algorithm first unions the endpoints of all existing links at no cost, even if they include cycles or duplicates. Sort candidate edges by nondecreasing cost. For each candidate, purchase it **only if** its endpoints are currently in different disjoint-set components. Union those components and add the cost to a long accumulator. Once only one component remains, stop. If candidates run out with multiple components, return -1.

## Why the greedy choice is safe

Consider the partition of vertices into current components. The next accepted edge is a cheapest candidate edge connecting distinct components. Kruskal's cut/exchange argument shows a minimum-cost completion exists that includes this choice: if a cheaper completion connects those components using some other crossing edge, exchanging the edge does not increase cost. Existing free links are already accounted for by the initial unions. Rejecting an edge whose endpoints are already connected prevents cycles that do not improve connectivity.

## Disjoint-set invariants

parent[x] points toward a representative root. find(x) returns that root, compressing the path so future queries become cheap. size[root] tracks component size; attach the smaller root to the larger root to keep trees shallow. union(a,b) returns false if both endpoints are already connected; otherwise it decreases the component count by one. Self-loops and duplicate links naturally return false after the first relevant union.

## Complexity

Sorting E candidates costs O(E log E). Processing P existing links and E candidates with weighted union and path compression costs O((P+E) alpha(n)) amortized; initializing n parents costs O(n). Total **O(n + E log E + (P+E) alpha(n)) time** and **O(n+E) extra space** for DSU and a cloned outer edge array. alpha(n) is the extremely slowly growing inverse Ackermann function. The input's edge arrays are not mutated; cloning the outer array is enough because sorting only reorders references.

## Common mistakes

- Using BFS/Dijkstra from node 0 to minimize individual distances: a shortest-path tree need not be an MST.
- Buying every cheapest-looking edge, including those that form cycles.
- Forgetting to union free existing links first.
- Returning cost even when not all components are connected.
- Adding costs to int rather than long (overflow).
- Accidentally sorting the caller's candidate array in place.
- Incorrect union-by-size updates or compressing parent[x] without returning the final root.
- Assuming n-1 *purchased* edges are needed even when some links are already installed.

## CS61B connections

Weighted quick union, path compression, asymptotic amortized reasoning, sorting, greedy exchange arguments, graph connectivity, and Kruskal MST. Compare Prim: Prim grows one connected tree via a priority queue; Kruskal grows many components by sorting edges and merging them.

## Java syntax

```java
int[][] sorted = candidates.clone();
Arrays.sort(sorted, Comparator.comparingInt(edge -> edge[2]));
long total = 0L;
if (dsu.union(u, v)) total += cost;
```

Use the existing graph/C++ review packet for an MST-versus-shortest-path decision chart.
