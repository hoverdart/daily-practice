# Second Distinct Dispatch Arrival — Solution notes

## Recognition signals and model
Weighted, positive edges plus a cost-minimization objective suggest Dijkstra. "Second distinct" means one distance per vertex is insufficient, while "walks allowed" means a prefix can be replaced without worrying about which vertices the suffix revisits. This is not the second shortest simple path problem.

## Brute force and why it fails
Enumerating walks can be infinite on an undirected graph with an edge, and even bounding costs can produce exponentially many walks. A cost-indexed reachability DP is a finite exact oracle for tiny weights: reachable[c][v] says some walk costs c and ends at v. Process costs in ascending order, propagating along every edge. If max weight is W, a shortest path costs <= (n-1)W, and inserting one backtrack on a path edge gives a distinct walk costing at most (n+1)W. When start=target use any incident edge twice; if isolated no second exists. Thus a bound of (n+1)W suffices for this undirected problem. This is pseudopolynomial O((n+m)nW) time as implemented with a 2D DP, O(n²W) space, infeasible for billion-weight links.

## Optimal reasoning: two-label Dijkstra
Maintain the smallest two distinct discovered costs for each vertex: first[v] < second[v] when both are finite. Initialize first[start]=0 and all other labels to infinity. Use a min-priority queue of (vertex,cost). On a nonstale pop, relax all outgoing edges with candidate=cost+w.

- candidate < first[v]: install it as first; demote the old first to second (it is smaller than the old second). Insert a ticket for the new first.
- first[v] < candidate < second[v]: replace second and enqueue it.
- Otherwise ignore the candidate, including equal-cost arrivals.

On demotion the old first's existing heap ticket remains usable. Since a newly discovered smaller cost comes from a strictly smaller popped cost, the old first could not already have been finalized. Do not enqueue it a second time. Skip any popped cost not equal to either current label. Stop only when the target's current second label is popped, not when it is first discovered.

## Why two labels suffice
Suppose a walk to a downstream vertex has a prefix to u with a cost that is third or worse among distinct prefix costs. There are two strictly cheaper distinct walks to u. Appending the same suffix to each is valid because revisits are allowed, and yields two strictly cheaper distinct total costs. Thus that prefix cannot be essential to a first or second distinct shortest walk. Dijkstra's nonnegative-weight ordering then finalizes the retained labels in increasing order; a better not-yet-discovered prefix would have an earlier heap predecessor, contradicting the minimum pop. A stale discarded label cannot become useful later, since the two smaller labels are achievable and can only improve.

## Example
One link 0--5--1, start 0, target 1. Pop (0,0), set first[1]=5. Pop (1,5), set second[0]=10. Pop (0,10), set second[1]=15. Pop (1,15), return 15. Stopping at 5 would answer a different question.

## Complexity
Each vertex's two distinct final labels are expanded at most once, with at most O(m) edge relaxations and heap insertions. A lazy heap can hold O(m+1) entries; O(n + m log(m+1)) time (including graph allocation), O(n+m) space. Equivalently for simple graphs one often writes O((n+m) log n); with arbitrary parallel edges the heap-size bound is clearer. The maximum relevant costs are O(nW), far below Long.MAX_VALUE under the constraints. No infinity label is added to a weight.

## Common mistakes
- Using a boolean visited array suppresses the second label.
- Counting two equal-cost routes as two arrivals violates distinctness.
- Never allowing revisits solves a different, harder problem.
- Overwriting first without retaining the old first loses candidates.
- Returning when second[target] is first assigned, rather than popped, can miss improvement.
- Using int distances or comparator subtraction overflows. Use long and Comparator.comparingLong.
- A disconnected target has no arrival; the isolated source=target has only cost zero.
- An undirected adjacency list needs both directions.

## CS61B connections
Adjacency lists, min-priority queues, lazy key updates, shortest-path relaxation, and greedy correctness. Contrast BFS (unit weights), ordinary Dijkstra (one best label), and this two-label generalization. Read the existing graphs review if you cannot explain the minimum-pop invariant without looking at code.
