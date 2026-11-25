# Latest Safe Dispatch — solution notes

## Recognition signals
Directed edges, different travel times, and deadlines on intermediate vertices. This is a path optimization, but ordinary shortest total travel time alone does not capture feasibility. The word "latest" and a fixed destination suggest working backward from the final deadline.

## Baselines
For tiny deadlines, enumerate start times and test time-expanded reachability, allowing wait/travel transitions. Time is a state dimension, impractical for 10^12. A much better baseline binary searches start time (earlier is never worse), running earliest-arrival Dijkstra each time while rejecting deadline violations. This is O(log(D+1) * (V+E log(E+1))) using a lazy heap, where D=deadline[s]. It works but repeats search. Forward Dijkstra minimizing raw travel time without checking intermediate closing times can return an invalid route.

## Derivation
Let latest[v] be the latest currently known feasible time to be at v and still reach t. Initialize latest[t]=deadline[t], other nodes=-1. For an incoming edge u->v taking w, a legal departure from u must satisfy departure<=deadline[u] and departure+w<=latest[v]. Thus
candidate=min(deadline[u], latest[v]-w).
Ignore negative candidates. A larger candidate dominates a smaller one, because starting earlier along the same suffix is always possible (all constraints are upper bounds). Relax when the candidate improves latest[u].

Use reversed adjacency lists (store u,w under v) and a **max** heap of (time,node). C++ priority_queue<pair<long long,int>> is already a max heap ordered lexicographically. Skip stale entries. Return when s is popped with its current label.

## Correctness: label-setting argument
Every nonnegative label constructed by relaxation corresponds to a feasible suffix (follow the known suffix from v, arriving no later than its label), so it never overestimates the true optimum. Let L*(v) denote the best feasible departure time. Because w>0, times strictly increase along a traversed edge and every feasible walk can be shortened by removing cycles. Consider the first non-stale heap extraction of a node x whose label allegedly falls short of L*(x). On a feasible route attaining L*(x), trace backward from t to the first not-yet-settled vertex y after a settled suffix. Its successor was settled correctly and relaxed y to at least the feasible departure time along that route. That time is >= L*(x) (and strictly greater if y is downstream of x). A current heap item for y must therefore have priority greater than the alleged label of x, a contradiction. For t itself its deadline is exact. Thus extracted labels are optimal, early exit is valid, and unlabelled s is impossible if the heap empties.

Example: t=3 has 18. Reverse relax 1 to min(7,18-3)=7, 2 to min(15,18-4)=14. Pop 2 first: relax 0 to min(20,14-5)=9. Pop 0: return 9, since no remaining route through label 7 can improve it.

## Complexity
Building adjacency and initializing labels costs O(V+E). Each vertex is settled at most once; each edge is examined at most once. Each successful improvement inserts one heap ticket, so there are at most E+1 tickets. Lazy-heap time O(V+E log(E+1)), space O(V+E). An indexed heap yields O((V+E) log V); with parallel edges, do not automatically replace log E by log V in the lazy analysis. This eliminates dependence on the magnitude of deadline values.

## Common mistakes
- Using a min heap by reflex instead of a max heap.
- Traversing outgoing edges from t instead of reversed edges.
- Applying the destination deadline to every predecessor instead of each node's own deadline.
- Subtracting w after capping with deadline[u]; these operations are not interchangeable.
- Rejecting time zero or treating -1 as a valid label.
- Returning when s is first discovered rather than when its current label is extracted.
- Ignoring stale entries; using 32-bit integers for deadlines.
- Assuming undirected links or forcing a cycle; waiting cannot improve an upper-bound deadline problem.

## CS61B connections
This is Dijkstra's label-setting proof with reversed direction and a maximization objective. The key monotonicity is candidate<=current time, analogous to nonnegative-weight forward distance relaxation. Compare BFS (uniform cost), Dijkstra (nonnegative costs), Bellman-Ford (negative weights), topological DP (DAGs), and the role of heaps and adjacency lists. A shortest path in hops or travel time alone is not the same as a latest feasible departure.
