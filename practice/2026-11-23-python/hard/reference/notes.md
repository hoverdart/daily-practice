# Solution notes — Maximum Unique Rewards from Start to Exit

## Recognition signals

Directed cycles, revisiting allowed, rewards counted **once per vertex**, and optimization of a *total reward* from start to target. This is not a shortest-path/min-heap problem. Within a **strongly connected component** (SCC), every room can reach every other, so a finite walk can visit all of them before exiting. Because rewards are **nonnegative**, collecting every room in that SCC never hurts. Contract SCCs to a **DAG** and find its maximum-weight start-to-target path.

## Baseline versus optimal

A state-space brute force tracks `(current_vertex, visited_vertex_subset)` and explores reachable states; there can be `O(n 2^n)` states and `O(m 2^n)` transitions (our small tests use this independent oracle). Counting only simple directed paths also fails because cycles allow extra reward. Optimal: two iterative DFS passes (Kosaraju) + condensation + Kahn topological DP, all `O(n+m)` time and `O(n+m)` space. This uses no recursion, so deep input graphs don't exhaust Python's call stack.

## Core invariants and proof

1. First DFS on original edges appends a vertex to `finish` **only after** all its reachable unexplored descendants are processed. The explicit stack tracks `(vertex, next_edge_index)` to reproduce recursive postorder.
2. Second DFS on reversed edges processes vertices in **decreasing** first-pass finishing time. Each traversal identifies exactly one SCC; different SCCs never merge.
3. Contracting SCCs cannot create directed cycles: a cycle of components would make their vertices mutually reachable, contradicting maximal SCCs.
4. For each SCC `c`, `weight[c]` is the sum of its nonnegative room rewards. Strong connectivity means a walk entering SCC `c` can visit every room and still reach any chosen outgoing edge; even `start == target` can collect a whole SCC before returning to the target.
5. `dp[c]` is the largest collectible reward on a path in the condensation DAG from the start SCC to `c`, including `c`'s full reward. Initialize `dp[startScc]=weight[startScc]` and `dp[others]=-1`. For each topologically processed edge `u→v` where `dp[u]` is reachable, relax `dp[v]=max(dp[v],dp[u]+weight[v])`.
6. Every directed walk induces a DAG path of SCCs (it can never return to a departed SCC), and each such DAG path can be implemented by a walk collecting all rewards in its visited SCCs. Therefore the DP optimum equals the original optimum.

## Compact pseudocode

```text
finish = dfs_postorder_iterative(graph)
component = dfs_components_iterative(reverse_graph, reversed(finish))
weight[c] = sum(rewards[v] for vertex v in SCC c)
for (u,v) in edges if component[u] != component[v]:
    DAG[component[u]].append(component[v]); indegree[component[v]] += 1
queue = all SCCs with indegree 0
best[startScc] = weight[startScc]
while queue:
    u = queue.popleft()
    for v in DAG[u]:
        if best[u] != -1: best[v] = max(best[v],best[u]+weight[v])
        indegree[v] -= 1
        if indegree[v] == 0: queue.append(v)
return best[targetScc]  # -1 when unreachable
```

## Common mistakes

- Assuming ordinary BFS or Dijkstra solves a **maximize unique rewards** goal.
- Collapsing all nodes reachable from a source into one SCC (reachability alone is not *mutual* reachability).
- Appending a node in DFS discovery order rather than *finish* order.
- Running the second pass on the forward graph instead of the reversed graph.
- Using recursive DFS for 100k-node chains; Python normally hits a recursion-depth limit.
- Summing rewards from both outgoing DAG branches: a single path cannot take two branches unless they reconverge via valid directed edges.
- Treating a zero-reward reachable state as unreachable; `-1` is an explicit sentinel.
- Deduplicating parallel DAG edges inconsistently with indegree updates; easiest is to keep each edge on both sides.

**CS61B:** directed graph representations, DFS and reverse graphs, component decomposition, DAG/topological sort, longest-path relaxation and DP, asymptotic analysis, iterative traversal.
