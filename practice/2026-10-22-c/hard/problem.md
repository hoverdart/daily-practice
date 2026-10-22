# Hard / Stretch — Critical Relay Links

A network has n relay stations numbered 0..n-1 and m **undirected** physical cables, indexed 0..m-1 in input order. A cable is **critical** (a bridge) if removing **only that cable** increases the number of connected components in the entire network.

Implement in C:

    typedef struct { int u, v; } Edge;
    int find_critical_links(int n, const Edge *edges, int m, int *out_ids);

Write all critical cable IDs into out_ids in **ascending input order** and return the count. Caller provides capacity m. Return -1 only if memory allocation fails. Do not modify edges.

**Important:** Parallel cables between the same endpoints are distinct; removing one of two parallel cables must not disconnect those stations. Self-loops are never bridges. The graph may be disconnected; isolated vertices are allowed.

**Examples:**
- n=4, edges (0,1),(1,2),(2,0),(2,3) → [3].
- n=2, edges (0,1),(0,1) → [].
- n=5, edges (0,1),(2,3) → [0,1].

**Constraints:** 1 ≤ n ≤ 100,000; 0 ≤ m ≤ 200,000; valid endpoints. Target **O(n+m)** time and space.

**Think:** During DFS, a tree edge (parent,child) is a bridge iff the child's subtree has no alternate edge to its parent or an ancestor. Track discovery time tin[v] and low[v] (earliest reachable discovery time via tree edges and at most one back edge). Skip the exact **parent edge ID**, not all edges to the parent vertex. Use iterative DFS to avoid C stack overflow on a 100,000-node chain.
