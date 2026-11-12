# Hard — Low-link bridges on an undirected multigraph

## Recognition signals

The question asks which **individual edges** are essential for *connectivity* if removed. This is a **bridge** problem, not shortest paths, not an MST, and not merely which edge belongs to some DFS tree. Unlike "mandatory on every shortest route", a bridge matters for *all* paths between the affected pieces.

## Brute force to optimal

For every cable e, delete it temporarily and DFS/BFS the entire network, counting components. With n+m work per deletion, this is **O(m(n+m)) time**, O(n+m) traversal/adjacency space. Testing whether endpoint reachability breaks after a deletion leads to a similar bound.

An **optimal Tarjan-style DFS low-link method** does one DFS of the complete undirected multigraph. Each vertex u gets:

- tin[u]: unique discovery time, assigned when u is first entered.
- low[u]: minimum discovery time reachable from u via zero or more DFS-tree edges down into its subtree, followed by **at most one back edge**. Once DFS(u) finishes, low[u] is final.

For a DFS tree edge (p,u), that cable is a bridge exactly when **low[u] > tin[p]**. If the subtree could reach p or an earlier ancestor through another cable, low[u] <= tin[p], and deleting the tree edge would not disconnect it.

## Iterative DFS invariant

The stack contains the active root-to-current-vertex path. cursor[u] is the next adjacency arc to process for each active u. When entering an undiscovered v, save parent[v]=u and parent_edge[v]=edge_id; initialize tin[v]=low[v]=clock and push v. An already discovered neighbor contributes tin[neighbor] to low[u] unless its arc is the **same cable ID** used to discover u. When cursor[u] exhausts, pop u; propagate low[u] to low[parent[u]] and test its tree cable before continuing.

**Parallel-edge trap:** two cables (p,u) have distinct IDs. Only the exact parent cable must be skipped. The other cable is a valid back edge and prevents either cable from being marked a bridge. Skipping by parent vertex instead incorrectly marks one parallel cable as a bridge.

**Self-loops:** their neighbor is the current vertex, so they cannot lower low[u] or be a DFS tree cable. They are never bridges.

**Disconnected graphs:** start a new DFS at every vertex with tin=-1; isolated vertices contribute no bridges.

## Runtime and space

Each of n vertices enters/exits the DFS once. Each of 2m adjacency arcs is scanned once. **O(n+m) time**. Adjacency arrays, tin/low, parent/edge IDs, cursor, and explicit stack cost **O(n+m) extra space**. The iterative stack handles a 200,000-vertex chain without relying on a potentially shallow C recursion stack.

## Common mistakes

- Check low[u] >= tin[parent] rather than the **strict** > condition for bridges (>= is used in a different articulation-point criterion).
- Skip every arc whose endpoint is the parent, breaking multigraph correctness.
- Ignore disconnected components by DFSing only vertex 0.
- Confuse directed edges with undirected cables; every cable needs two adjacency arcs.
- Forget self-loops or assume there are no parallel edges.
- Update a parent's low before the child has finished.
- Reuse DFS stack frame state incorrectly; cursor must survive child traversal.
- Allocate O(n*m) memory or recursively DFS a 200,000-vertex path.
- Forget the caller owns result.flags and must free it.

## CS61B connections

Core ideas: adjacency lists (here manually implemented using head/to/next arrays), DFS tree edges, edge classification, connectivity, and explicit stacks. It also prepares you for articulation points and biconnected components. Unlike **Kruskal/union-find**, which can construct connectivity from added edges, low-link DFS answers what happens when **each existing edge is deleted** in one pass.

