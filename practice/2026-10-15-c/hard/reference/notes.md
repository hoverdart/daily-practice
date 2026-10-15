# Reference Notes — Cheapest Route with Rebates

## Recognition signals
Directed weighted graph plus **negative edges** rules out ordinary Dijkstra. A repeatable negative cycle can make minimum cost unbounded. The subtlety is that the cycle matters only if it is reachable from src and has a route onward to dst.

## Brute force vs optimal
Enumerating all paths is exponential even without cycles. Floyd-Warshall answers all-pairs questions in O(V³) time/O(V²) space, but this problem asks for one source/destination and gives an edge list. Bellman-Ford is a better fit.

Initialize dist[src]=0, all other distances to a large sentinel. Scan every edge up to n-1 times, relaxing u→v whenever dist[u] is finite and dist[u]+weight is smaller than dist[v]. Stop early if no relaxation occurs.

## Why n-1 passes?
After i passes, distances are no greater than the cheapest walk using at most i edges; in-place relaxation may discover longer walks sooner. Any finite shortest path can be chosen simple and has at most n-1 edges. If a reachable negative cycle affects the destination, no finite minimum exists.

## Negative-cycle relevance
A still-relaxable edge after n-1 passes indicates the influence of a reachable negative cycle. But the destination might not be reachable from that cycle. Mark can_reach_dst[dst]=true. Repeatedly scan the original edges: if v can reach dst and u→v exists, mark u. At most n-1 scans suffice. If a still-relaxable edge u→v has finite dist[u] and can_reach_dst[v], return 1. Otherwise return -1 if dst is unreachable, or 0 and the finite cost.

## Complexity and memory
Distance relaxation takes O(VE), reverse reachability takes O(VE), and the final check O(E). Space is O(V). Allocate distance and reachability arrays, free them on every return path, and use long long. Never add to the infinity sentinel without checking reachability.

## Common mistakes
- Using Dijkstra with negative weights.
- Treating every negative cycle as relevant, including isolated ones.
- Missing negative self-loops, parallel edges, or src==dst.
- Confusing unreachable (-1) with unbounded (1).
- Overwriting *out for unsuccessful results.
- Forgetting free on early return.

## CS61B connections
All shortest-path algorithms depend on **edge relaxation**. Use BFS for unit weights, 0–1 BFS for binary weights, Dijkstra for nonnegative weights, Bellman-Ford for negative weights and cycle detection, and topological DP for DAGs. A follow-up is path reconstruction via parent pointers, or reverse reachability via a reverse adjacency list and BFS in O(V+E).
