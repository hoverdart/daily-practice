# Notes — Battery-Aware Relay Route

## Recognition signal
Nonnegative weighted graph plus minimum-cost route suggests Dijkstra. The one-use token means future options depend on both node and whether the token has been spent.

## Brute force
Choose each edge as discounted and rerun shortest path, repeating nearly identical work O(m) times.

## Optimal approach
Use state `(node, token_used)`. Each node has two layers. From an unused-token state, traverse normally or at `weight // 2` and switch to used. From a used-token state, only normal traversal remains. Run Dijkstra on this implicit graph.

Time: O((n + m) log n). Space: O(n + m).

## Invariant
When a non-stale state is popped, it has the cheapest unsettled distance for that exact state. All transition costs are nonnegative.

## Common mistakes
- Keeping one distance per node and merging different future options.
- Assuming the token must be used.
- Using BFS despite unequal edge weights.
- Forgetting stale-entry checks with `heapq`.

## CS61B connection
Combines adjacency lists, priority queues/heaps, and Dijkstra relaxation. State expansion is useful when shortest paths include a limited resource or mode.
