# Explanation — Cheapest Transfer with Refund Loops

## Recognition signals
Signed edge weights, repeated vertices, and a single-source minimum-cost walk are Bellman–Ford signals. A cycle matters only if reachable from start **and** able to reach target. Distinguish three cases: no walk, finite optimum, or no finite lower bound.

## Why the obvious approaches fail
BFS minimizes hops, not weighted cost. Dijkstra's settled-label argument depends on nonnegative edges: in example 1 the target may pop at cost 2 before a later negative edge produces -5. Enumerating simple paths is exponential and cannot detect arbitrarily beneficial walks. Floyd–Warshall solves all-pairs paths in O(n^3) time and O(n^2) memory, unnecessary here.

## Algorithm
1. Reverse all directed edges. BFS from target to find vertices that can reach target in the original graph. If start is not marked, return null.
2. Restrict Bellman–Ford to edges whose endpoints are marked. Let R be the number of marked vertices, M the number of retained edges. Initialize dist[start]=0 and all others=Infinity.
3. Perform up to R-1 complete edge passes. For each edge u->v, if u is reachable by a known walk, relax dist[v] using dist[u]+w. Updates are in-place. If an entire pass changes nothing, return dist[target].
4. Scan the edges once more. If any reachable edge can still improve its destination, return "UNBOUNDED"; otherwise return dist[target].

## Correctness invariant
Each finite dist is the cost of some actual start-to-vertex walk, so no invented route is used. After k full passes every walk of at most k edges has been considered in the sense that the label is no larger than its cost (in-place updates may discover longer walks sooner). If no reachable negative cycle exists in the filtered graph, any minimum walk can be shortened to a simple path by removing cycles of nonnegative cost, using at most R-1 edges. Therefore after R-1 passes all finite optimum labels are exact, and no edge can improve them.

Conversely, if a reachable negative cycle exists, every cycle vertex has a finite label after R-1 passes. If no edge on that cycle were relaxable, summing dist[v] <= dist[u]+w around it would yield 0 <= total cycle weight, a contradiction. An additional improvement therefore detects a reachable negative cycle; all filtered vertices can reach target, so repeating the cycle before continuing makes the final fee arbitrarily negative. A negative cycle that cannot reach target was removed; one unreachable from start is ignored by the finite-label check. A complete unchanged pass is a fixed point, so further passes cannot change it.

## Example trace
For edges [0,1,5], [0,2,2], [1,2,-10], all vertices can reach 2. Initial labels [0,inf,inf]. The first pass produces [0,5,-5]; second pass makes no changes. For example 3 the 1->2->1 cycle totals -4, so every pass around it can decrease the fee and still continue to 3.

## Complexity
Reverse adjacency and reachability cost O(n+E) time and space. Filtering costs O(E). At most R-1 passes and one final scan cost O(R*M), at most O(nE); overall O(n+E+R*M) time, O(n+E) auxiliary space. This is the standard Bellman–Ford bound for general signed edges, not a claim that every input must require that much time. Early exit and filtering often reduce the work. The constraints allow at most roughly 10^7 relaxations, with magnitude at most roughly 10^13 even under in-place negative-cycle updates, within Number.MAX_SAFE_INTEGER.

## Common mistakes
- Returning a finite value on the first arrival at target, or stopping after one scan because it happens to work on forward-ordered edges.
- Treating any negative edge or any negative cycle anywhere as unbounded.
- Forgetting reverse reachability uses edges reversed, not the original outgoing edges.
- Using a visited set to prohibit repeated vertices, or using Dijkstra despite negative fees.
- Skipping the final scan; marking unreachable vertices as affected; confusing null, 0, a negative finite value and "UNBOUNDED".
- Returning 0 immediately for start=target; a reachable cycle that returns to start can change the answer.
- Using Array.shift for BFS instead of a head index, or creating shared adjacency arrays with Array(n).fill([]).

## CS61B connection
Adjacency lists, directed graphs, BFS visited marking, reachability, and edge relaxation are core material. Bellman–Ford extends Dijkstra-style relaxation to negative weights by replacing greedy heap ordering with repeated edge passes. Compare BFS (unit weights), Dijkstra (nonnegative), DAG topological relaxation (signed weights but no cycles), Bellman–Ford (general signed weights), and Floyd–Warshall (all pairs).

## Transfer
If the graph is a DAG, a single topological-order relaxation pass handles even negative edges in O(n+E). If all fees are nonnegative, a heap-based Dijkstra typically scales better. If every affected destination must be reported, start from vertices still relaxable after the final pass and traverse forward.
