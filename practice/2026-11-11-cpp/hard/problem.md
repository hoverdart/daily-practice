# Hard / Stretch — Rerootable Org Chart Queries

An organization has n employees connected by n-1 mentor relationships. Ignoring direction, the relationships form a **tree**. Employee IDs are 0 through n-1. The CEO of the day (the root) can change, which changes who is considered the ancestor of whom — but **does not change the underlying edges**.

Initially employee 0 is the root. Process a sequence of two kinds of requests:

- **R(r)**: change the root to employee r.
- **Q(u, v)**: report the lowest common ancestor of u and v under the **current** root.

The lowest common ancestor is the common ancestor farthest from the current root (a node is its own ancestor). Return the answers to every Q request in order.

Implement:

~~~cpp
struct AncestorRequest {
    char type;  // 'R' or 'Q'
    int x;      // new root for 'R'; u for 'Q'
    int y;      // ignored for 'R'; v for 'Q'
};
std::vector<int> rerootedLcaQueries(
    int n,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<AncestorRequest>& requests);
~~~

### Example

- n=5, edges: (0,1), (1,2), (2,3), (3,4), a chain.
- Requests: Q(1,4), R(4), Q(1,4), Q(1,3), R(2), Q(0,4)
- Output: [1, 4, 3, 2]

### Constraints

- 1 <= n <= 200,000
- Edges form a connected, undirected tree; exactly n-1 edges.
- 0 <= employee IDs < n
- 0 <= requests.size() <= 200,000
- Every request has a valid type and employee IDs.
- Target O((n + requests.size()) log n) time and O(n log n) preprocessing space, excluding output.
- **Avoid recursion depth risks** on a chain with 200,000 vertices.
- Do not BFS/DFS from scratch after each root change.

### Before coding

Preprocess ancestry once from a *fixed* root, say 0. A new root r does not change the tree's paths. Can you express LCA under r using only three ordinary fixed-root LCA computations?

Hint for a later attempt: inspect LCA_0(u,v), LCA_0(u,r), and LCA_0(v,r), comparing their original-root depths.
