# One Discounted Relay Toll — Recognition and Detailed Notes

## Recognition signals

A graph with **nonnegative weighted edges** asks for minimum total cost, so Dijkstra is a starting point. A **one-time resource** (coupon, exception, power-up, key, extra step) signals **state-space expansion**: the state must include both the location and whether the resource remains available. The optimization cannot be represented by a single distance per physical router.

## Brute force / baseline versus optimal

**Brute force:** Enumerate every simple directed source-to-target path, select at most one edge to discount, and take the minimum. A graph can have exponentially many simple paths, and cycles make naive unrestricted route enumeration non-terminating.

**Correct but slower baseline:** Build two layers, each with n states. A state (v,0) means the coupon is unused, (v,1) means it has been used. Expand each original directed (u,v,w) into:
- (u,0) -> (v,0) of cost w (do not redeem)
- (u,0) -> (v,1) of cost floor(w/2) (redeem now)
- (u,1) -> (v,1) of cost w (coupon already spent)

Run Bellman-Ford on the expanded graph: O((2n)(3m)) = O(nm) time, O(n+m) memory. It works because expanded weights are nonnegative, but wastes the special property Dijkstra can exploit.

**Optimal:** Run lazy binary-heap Dijkstra directly on (router,used) states. Keep dist[v][0] and dist[v][1] separately. Initialize dist[source][0]=0; push (0,source,0). Relax ordinary edges within the same layer, and the discounted transition only when used=0. Ignore stale heap entries. The first nonstale state popped whose vertex is target gives the answer, whether the coupon was used or not.

## Correctness reasoning

Every legal original route with at most one coupon redemption corresponds to exactly one expanded-graph path with the same cost, obtained by switching layers at the discounted traversal (or staying entirely in layer 0). Conversely every expanded path switches at most once from 0 to 1, so it describes a legal original route and its correct toll.

All expanded edge costs are >= 0, including the discounted floor(w/2). Dijkstra's invariant therefore applies: the first nonstale pop of each state has minimum cost among all paths reaching it. In particular, the first target state popped across both layers is globally optimal; no cheaper target state can remain undiscovered. If neither target state is reachable, return -1.

**Why one distance per router fails:** suppose reaching hub H costs 4 with the coupon already spent, or 7 while retaining the coupon. If the next link costs 100, the two completions cost 104 and 57 respectively. A single dist[H]=4 would discard the better continuation.

## Complexity

The expanded graph has V'=2n vertices and E'<=3m edges. With adjacency lists, one binary heap, and lazy deletion, Dijkstra takes O((V'+E') log(V'+E')) = **O((n+m) log(n+m)) time** (for n+m >= 2) and O(n+m) extra space for graph, distances and potentially queued relaxations. Ties, parallel edges and self-loops are safe. When source == target, the initial heap pop returns 0.

## Common mistakes

- Reversing directed links or building an undirected adjacency list.
- Keeping a single dist per router; coupon availability changes future decisions.
- Redeeming the coupon repeatedly because used is never updated.
- Applying the coupon only to the most expensive edge globally; the chosen route can change when the coupon is applied.
- Using regular division (/), producing fractional tolls, rather than floor integer division (//).
- Using BFS or a deque 0-1 BFS when original costs can be arbitrarily large.
- Marking a vertex visited when **pushed**, not when **popped** with minimum nonstale distance.
- Omitting stale-entry checks after a cheaper path has been discovered.
- Assuming the coupon must be used (the problem permits zero uses).
- Failing on source == target, unreachable destinations, zero weights, parallel edges or self-loops.
- Using an arbitrary finite sentinel smaller than a valid total toll.

## Python / CS61B connections

The adjacency list (list of lists of (neighbor,weight) tuples) is CS61B's sparse-graph representation. heapq gives a **min-priority queue**; use heappush(heap, (new_cost, vertex, state)) and heappop(heap). The algorithm is repeated **edge relaxation** under Dijkstra's finalized-distance invariant, with a richer state graph. This is closely related to BFS on a state-space graph (such as a grid with keys), except arbitrary nonnegative costs require Dijkstra instead of FIFO order.

A smaller independent Bellman-Ford oracle is valuable for testing: it is slow, but uses a genuinely different relaxation order, so randomized cross-checking is more convincing than writing a test that copies Dijkstra's logic.
