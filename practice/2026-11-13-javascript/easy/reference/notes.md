# Easy reference — First Full Network Merge

## Recognition signals

Links are added to an **undirected** graph and queries ask when the entire structure is **connected**, not how short a route is. Use the CS61B **disjoint-set union (union-find)** structure: incremental connectivity and union by size/path compression.

## Brute force vs optimal

After every installed link, build an adjacency list and BFS/DFS from station 0. When all n vertices are visited, return the prefix length. Repeating traversal can cost **O(m(n+m)) time** for m links (and O(n+m) memory). An incremental adjacency list reduces rebuilding but not repeated searches.

With DSU, initially each station is one group. For every link, find both **root representatives**. If distinct, union their sets and decrement group count. Duplicate or self-links already lie in the same component and do not reduce it. Return i+1 on the first group count of 1; this is a count of processed events, not an index. For n<=1, return 0.

## Proof and invariant

After k events, `find(u) === find(v)` iff a path exists between u and v among those k undirected links. It holds initially for only identical vertices. Adding one link merges exactly the components containing its endpoints and preserves the equivalence. Therefore the maintained group count equals the number of connected components; group count 1 is exactly global connectivity. The earliest such prefix is correct.

## Complexity

O(n) initialization, then m finds/unions at **amortized O(α(n))** each with both path compression and union by size: **O(n + m α(n)) time, O(n) auxiliary memory**, where α is inverse Ackermann. This is near constant, not a formal worst-case O(1) bound.

## Common mistakes and CS61B connections

Do not decrement for duplicate links, union non-root nodes, mistake 0-based indices for event counts, or forget the zero/one-station convention. DSU belongs to CS61B weighted quick union, path compression, amortized algorithms, dynamic connectivity, and Kruskal's MST. BFS/DFS is an alternative for a static graph, not as convenient for a stream of edge insertions.
