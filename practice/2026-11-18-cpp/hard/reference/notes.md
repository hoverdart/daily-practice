# Optimal explanation — Critical Firmware Rollout Chains

## Recognition signals

The prompt describes **prerequisites**, a **DAG**, task durations, and a **critical path**. Directed edges impose an ordering; a topological sort exists. To minimize the project's completion time with unlimited concurrent workers, every prerequisite chain must fit, so the earliest completion is the **maximum path duration**, not an ordinary shortest-path problem. To identify **all** critical nodes/edges without enumerating paths, compute best paths on both sides of every node.

## Brute force versus optimal

**Brute force:** enumerate all directed paths, sum their task durations, and collect every task/edge from paths achieving the maximum. A DAG can have exponentially many paths (e.g. layered branching), so this is exponential in n and unsuitable for n=100,000. Maintaining the current path uses O(n) extra stack/state excluding stored answers.

**Optimal:** build adjacency lists and indegrees, run Kahn's algorithm to generate one topological order. Then calculate:

- ending[u] = maximum total duration of any directed path **ending** at u, including u.
- starting[u] = maximum total duration of any directed path **starting** at u, including u.
- M = max(ending[u]) across all tasks (or 0 for empty input).

Initialize ending[u]=starting[u]=duration[u] to permit a single-task path. Process edges u->v in topological order:

~~~cpp
ending[v] = max(ending[v], ending[u] + (long long)duration[v]);
~~~

Then process u in **reverse** topological order and all outgoing edges u->v:

~~~cpp
starting[u] = max(starting[u], (long long)duration[u] + starting[v]);
~~~

A task u belongs to some critical chain iff:

~~~cpp
ending[u] + starting[u] - duration[u] == M
~~~

An edge with input index i, endpoints u->v, belongs to some critical chain iff:

~~~cpp
ending[u] + starting[v] == M
~~~

Iterate task IDs and input edge indices in natural order to produce sorted results without sorting.

**Time:** O(n+m), since indegrees, topological order, two DP passes, and classification each scan vertices/edges a constant number of times. **Auxiliary space:** O(n+m) for adjacency, indegrees, order, DP arrays, queue, and output. Each path may hold up to n tasks of 10^9 duration, so sums must be 64-bit.

## Invariants and proof

- **Topological order:** when processing u, all predecessor nodes have already propagated their best ending values. Therefore ending[u] is finalized when u is processed. By induction over the order, the forward recurrence yields the longest path ending at each vertex.
- **Reverse order:** when processing u backward, all successors already have finalized starting values. The symmetric recurrence computes longest paths starting at u.
- **Task classification:** concatenate a longest path ending at u with a longest path starting at u, counting u once. In a DAG, their only common vertex can be u; any other repetition would imply a directed cycle. Therefore this forms a valid path with duration ending[u]+starting[u]-duration[u]. If that equals M, u lies on a critical chain; if it is smaller, none can contain u.
- **Edge classification:** concatenate a longest path ending at u, the edge u->v, and a longest path starting at v. The two paths cannot intersect in a DAG with u->v, so this is valid and has duration ending[u]+starting[v]. Equality with M characterizes membership. Duplicate edges are distinct paths by edge identity, so report each corresponding input index.

## Mistakes to anticipate

1. Use a minimum-distance algorithm (BFS/Dijkstra); this is a maximum-cost dependency **chain**.
2. Treat all tasks as a serial sum; independent tasks can execute concurrently.
3. Set DP baseline to zero without including each task's own duration, or count the task twice when joining prefix and suffix.
4. Classify only a single reconstructed longest path; the task asks for the union over all ties.
5. Forget disconnected or zero-duration components. If the maximum duration is zero, even isolated tasks and zero-duration edges lie on some maximum path.
6. Treat input edge indices as unique endpoint pairs; duplicate dependencies must each be classified.
7. Recursively DFS a 100,000-task chain and overflow the call stack; Kahn with a queue is iterative.
8. Use 32-bit int sums; up to 100,000 × 10^9 requires long long.

## CS61B and interview transfer

Kahn's algorithm combines a queue with indegree accounting. The two DP recurrences are edge relaxations in a topological order; unlike Dijkstra, **even negative weights** would be safe for weighted DAG shortest paths if an appropriate unreachable/base condition were used. For this project's nonnegative durations, each task may itself start a path.

These arrays mirror longest-chain scheduling and critical-path analysis, and resemble rerooting/tree DP in their forward/backward decomposition. A useful retrieval drill: derive the classification formula from a five-node example with two equal-duration critical chains, then explain the O(V+E) proof aloud.
