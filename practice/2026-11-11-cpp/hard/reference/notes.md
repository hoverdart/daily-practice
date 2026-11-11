# Hard / stretch solution notes — Rerootable Org Chart Queries

## Recognition signals

- A connected graph with n-1 edges is a **tree**: every pair of vertices has a unique undirected path.
- Questions ask about **ancestors and LCA** with **many queries**, so repeated BFS from every root is too slow.
- A **changing root** changes ancestor directions, not the graph topology; reuse a fixed-root preprocessing structure.
- Constraints n,q <= 200,000 suggest O((n+q) log n) rather than O(nq).

## Brute force versus optimal

**Brute-force baseline:** for each Q, BFS from the current root to find parents, walk u's ancestor chain into a set, and climb from v to the first marked node. O(n) per query, O(n) additional memory, O(nq) worst-case total time. Rebuilding only after R can still be O(nq) when root changes frequently.

**Optimal:** preprocess binary lifting with root 0. The tree depth and 2^j ancestors of every node are fixed. Ordinary LCA_0(a,b) costs O(log n) after O(n log n) preprocessing. For Q(u,v) under current root r, compute:

- x = LCA_0(u,v)
- y = LCA_0(u,r)
- z = LCA_0(v,r)

The deepest of x,y,z according to **depth from root 0** is the required LCA_r(u,v). Each R is O(1); each Q is O(log n). Overall O(n log n + q log n) time, O(n log n) space plus O(q) output. The O(n) adjacency list is included.

## Binary lifting invariant

~~~cpp
up[0][v] = parent[v];  // root 0 is its own parent
up[j][v] = up[j-1][ up[j-1][v] ];
~~~

At every j, up[j][v] is the ancestor 2^j edges above v, saturating at root 0. Lift a deeper node by the bits of the depth difference. If nodes are then unequal, inspect powers from largest to smallest and lift both only when their ancestors differ; this keeps them strictly below their LCA until the final parent step.

The iterative traversal avoids stack overflow on a path of 200,000 nodes. A BFS queue vector with a moving head index is sufficient.

## Why the reroot identity works

Think of the unique three paths between u, v, and r. Their common junction is the **tree median** of these three vertices: the point where the u-to-r and v-to-r paths first join on the way toward r. That is exactly LCA_r(u,v).

Fix root 0. Let x = LCA_0(u,v).

- **r lies outside x's descendant subtree:** the paths from u and v first converge at x while moving toward r; y and z are at x or above it. Deepest candidate is x.
- **r lies inside x's descendant subtree:** the root enters through one of x's child branches (or at x). The LCA under r moves onto that branch, to LCA_0(u,r) or LCA_0(v,r), whichever is deeper; the other candidates cannot be deeper.

Thus one of x,y,z equals the rerooted LCA; the deepest by fixed-root depth selects it. No full rerooting is needed.

## Important C++ snippets

~~~cpp
std::vector<std::vector<int>> adj(n);
for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

std::vector<int> order{0};
for (std::size_t head = 0; head < order.size(); ++head) {
    int u = order[head];
    // Visit all unvisited neighbors; append each to order.
}

int levels = 1;
while ((1LL << levels) <= n) ++levels;
std::vector<std::vector<int>> up(levels, std::vector<int>(n));
~~~

## Common mistakes

1. Rebuilding the entire rooted tree when R changes, causing O(nq) worst-case.
2. Using the **shallowest** of three fixed-root LCAs; the correct node is the deepest.
3. Comparing depths in the **current** root instead of in preprocessed root 0.
4. Forgetting that a node is an ancestor of itself.
5. Returning the wrong node for u=v or when r equals u/v.
6. Using recursive DFS on a chain of 200,000 employees.
7. Failing to lift the deeper node to equal depth before synchronizing ancestors.
8. Computing 1 << bit as a 32-bit signed shift unnecessarily; use 1LL for the table size.

## CS61B connection

Tree DFS/BFS, adjacency lists, parent/depth arrays, binary search/doubling, logarithmic query structures, and LCA reasoning directly extend the CS61B graph and tree curriculum. This is a tree problem disguised as a changing hierarchy; the key transfer skill is to fix the topology while changing the interpretation of the root. A useful follow-up is implementing path-distance queries as depth[u]+depth[v]-2*depth[LCA_0(u,v)].
