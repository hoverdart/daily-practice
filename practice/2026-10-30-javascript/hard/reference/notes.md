# Explanation — Critical Route Count in a DAG

## Recognition signals
"Directed dependencies," "no cycles," "maximum route score," "negative weights," and "count optimal routes" point to **topological ordering + dynamic programming**, not ordinary shortest-path BFS or Dijkstra. DAG longest paths are tractable even though longest simple paths in general directed graphs are computationally hard.

## Brute force versus optimal
**Brute force:** recursively enumerate every directed path from start to target, score it, and count ties. The number of paths can be exponential in n even in a DAG (a 40-layer diamond has `2^40` routes).

**Optimal:** build adjacency lists and indegrees. Kahn's algorithm gives a topological order. Track `best[v]` (maximum score from start, initialized to `-Infinity`) and `ways[v]` (number of maximizing routes mod 1e9+7). Initialize `best[start]=0, ways[start]=1`. For each outgoing edge `u -> v` of weight w:
- If u unreachable, skip score relaxation.
- If `best[u]+w > best[v]`, **replace** `best[v]` and `ways[v]=ways[u]`.
- If scores tie, **add** `ways[u]` modulo MOD.
- Otherwise do nothing.
Always decrement `indegree[v]`, even if u is unreachable, so the entire DAG is processed in valid order.

Runtime `O(n+m)`; memory `O(n+m)` for adjacency, indegrees, DP arrays, and queue. The queue uses a numeric head pointer rather than `Array.shift()`, which may move elements repeatedly.

## Correctness invariant
When Kahn removes u from the queue, **all incoming predecessors of u have already been processed**. Every path from start to u (other than the zero-edge start path) ends with one such predecessor edge. By induction on topological order, each predecessor already stores the correct maximum score and number of routes achieving it. Taking the maximum over all incoming candidates computes the correct `best[u]`; summing counts **only on ties** counts all and only maximum routes. Distinct predecessor edges correspond to distinct routes (duplicate directed edges are excluded). Since no directed cycle exists, no path can revisit a vertex, and start=target has exactly the empty route.

## Negative weights, reachability, and numbers
- `-Infinity` marks unreachable; `0` would incorrectly beat valid negative paths.
- Edge weights may be negative: this is fine because topological order settles predecessors first. Ordinary Dijkstra assumes nonnegative edges and is a **minimum**-distance algorithm.
- The maximum possible absolute path sum is at most `(n-1)*1e6 < 1e11`, safely inside JavaScript's exact-integer range `2^53-1`.
- Counts are reduced modulo `1_000_000_007` at each addition. Adding two already-reduced counts stays under `2.1e9`, also exactly representable.
- If target is unreachable, return `{maxWeight:null, ways:0}`, not a fabricated zero-length path.

## Common mistakes
- Assuming vertex IDs are topological order (the fixed test deliberately violates this).
- Counting all routes instead of only **maximum-score** routes.
- Forgetting to reset `ways[v]` when a strictly better candidate arrives.
- Using `>=` for both update cases, double-counting or losing ties.
- Skipping indegree updates for unreachable predecessors, preventing later vertices from entering the queue.
- Initializing `best` to zero or using a greedy min-heap with negative weights.
- Recursive DFS on a 120,000-stage chain, or `queue.shift()` at every step.
- Missing the empty route when start=target.

## CS61B connections
Kahn's topological sort, adjacency lists, DAGs, edge relaxation, and dynamic programming over graph structure. Dijkstra settles vertices in increasing distance under **nonnegative** weights; DAG DP instead settles vertices after **all predecessors** are ready. Counting ties is an additional DP state that reappears in shortest-path counting, edit-distance variants, and scheduling.
