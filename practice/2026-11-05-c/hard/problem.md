# Hard / Stretch — Mandatory Edges on Every Fastest Route

A communications network is a **directed, unweighted multigraph** with vertices 0 through n-1. A route is a sequence of directed edges. Each edge traversal costs exactly one hop. Parallel edges are distinct physical links even when they have the same endpoints.

For a given source s and target t, find **every original edge ID that appears in every minimum-hop route from s to t**. An edge ID is its zero-based index in the input array. Return the IDs in increasing order.

Implement:

~~~c
typedef struct { int from, to; } DirectedEdge;
typedef struct { int *indices; int count; } MandatoryEdges;

MandatoryEdges mandatory_fastest_links(
    int n, const DirectedEdge *edges, int m, int source, int target);
~~~

The returned indices array, if non-NULL, is **heap allocated** and owned by the caller, who will call free on it. If t is unreachable from s or source == target, return {NULL, 0} (a zero-edge route contains no mandatory edges).

### Examples

1. Edges indexed 0:(0->1), 1:(1->3), 2:(0->2), 3:(2->3), 4:(3->4); s=0, t=4. The two shortest routes share only edge 4; answer [4].
2. Edges 0:(0->1), 1:(0->1), 2:(1->2); s=0, t=2. Either parallel edge can start the route, but edge 2 is compulsory; answer [2].
3. No s-to-t route: answer empty.

### Constraints

- 1 <= n <= 100,000; 0 <= m <= 250,000
- 0 <= from, to, source, target < n
- Self-loops and parallel directed edges are allowed.
- Target **O(n+m)** time and O(n+m) extra space.
- Repeatedly deleting an edge and running BFS is too slow on large inputs.

### Hints to reason about, not to blindly implement

First find the minimum distance D from s to t. For which directed edges u->v can some shortest route pass through that edge? Look at distFromS[u] and distToT[v] (from a BFS on the **reversed graph**). Every shortest route crosses each BFS layer boundary once. What happens if exactly one eligible physical edge crosses a given boundary?

