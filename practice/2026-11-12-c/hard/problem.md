# Hard / Stretch — Which Cables Are True Bridges?

You maintain an **undirected** network of n stations and m individual cables. A cable has an ID equal to its input index. The graph may be disconnected, may contain **parallel cables** connecting the same endpoints, and may contain **self-loops**.

A cable is a **bridge** if deleting only that cable increases the total number of connected components in the graph. Report exactly which cable IDs are bridges, preserving input-index order.

Implement in solution.c:

~~~c
typedef struct { int u, v; } Cable;
typedef struct {
    unsigned char *flags; /* length m; flags[e]=1 iff cable e is a bridge */
    int count;
} BridgeReport;

BridgeReport find_bridges(int n, const Cable *edges, int m);
~~~

For m>0, return a malloc/calloc-allocated flags buffer of m bytes, initialized to 0 or 1; the caller frees it. For m=0, return {NULL,0}. You may assume successful allocation on valid inputs in this exercise.

## Examples

- n=4, edges=[(0,1),(1,2),(2,0),(2,3)] -> flags [0,0,0,1], count=1.
- n=2, edges=[(0,1),(0,1)] -> flags [0,0], count=0. Two parallel cables protect each other.
- n=3, edges=[(0,0),(0,1),(1,2)] -> flags [0,1,1], count=2.
- n=5, edges=[(0,1),(1,2),(3,4)] -> all three bridges (disconnected input is valid).
- n=0,m=0 -> {NULL,0}.

## Constraints

- 0 <= n <= 200,000; 0 <= m <= 300,000.
- For each cable, 0 <= u,v < n. There can be parallel cables and self-loops.
- Required **O(n+m) time, O(n+m) extra memory**.
- Use an **iterative DFS** to avoid overflowing the C call stack on a long chain.

## Interview questions

1. Why doesn't an edge within a cycle disconnect the graph when removed?
2. Define discovery time tin[u] and low[u] precisely.
3. On DFS tree edge u -> v, why is it a bridge iff low[v] > tin[u]?
4. Why must you skip the *parent edge ID*, not every edge to the parent vertex?
5. How can an explicit stack resume iterating neighbors after a child returns?
6. How should self-loops, isolated stations, and disconnected components behave?

