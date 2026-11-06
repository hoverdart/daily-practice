# Cheapest Compliant Deployment Order — Recognition and Detailed Notes

## Recognition signals

Dependencies ("a must precede b") form a **directed graph**, and a legal deployment sequence is a topological order. However, this is *not just* topological sorting: the cost depends on **which module immediately precedes the next**. With only n <= 15, the small size is a strong signal for **bitmask dynamic programming**.

## Brute force versus optimal

**Brute force:** Enumerate all permutations and reject those violating prerequisites; compute each valid permutation's transition cost. O(n! * (n+m)) if checking each permutation naively, using O(n) recursion state (plus input). A backtracking topo-order generator prunes illegal prefixes, but worst-case remains factorial on a graph with no edges.

**Optimal:** For each task v, make a bitmask needed[v] of all immediate prerequisites. Let dp[mask][last] be minimum switch cost to deploy exactly the tasks in mask, ending at last. Impossible states are Infinity. Initialize dp[1<<first][first]=0 when needed[first]=0, because the first deployment has no incoming switch. For each finite state, append any unused next whose needed bits are all inside mask. Relax:

~~~text
newMask = mask | (1 << next)
dp[newMask][next] = min(dp[newMask][next],
                        dp[mask][last] + switchCost[last][next])
~~~

The answer is min(dp[allTasks][last]) across last, or -1 if no state is reachable. For n=0, answer 0.

We may initialize by a synthetic sentinel last=n instead, but direct first-task initialization saves a factor in memory.

## Correctness invariant and proof

For every reachable (mask,last), dp is the minimum cost of any prerequisite-respecting partial sequence whose deployed set is exactly mask and whose final task is last. Base: singleton tasks with no prerequisites have cost 0, and all other singleton states are impossible. Induction: any valid nonempty sequence with more than one task has a valid prefix ending at some previous task; its final task's prerequisite bits all appear in that prefix. The recurrence considers this predecessor and adds the exact transition cost. Conversely, every transition appends a new task only after all its prerequisites, preserving legality. The minimum thus captures all and only valid sequences.

Every step sets one new bit: masks strictly increase, so integer-order iteration processes predecessor states before successors. No recursive stack or cycle detector is needed. A directed cycle cannot yield a complete reachable mask, so the answer is -1.

## Complexity

Precompute prerequisite masks in O(m+n). At most n*2^n states and n candidate appended tasks per state. Time O(m+n^2*2^n), memory O(n*2^n+n) including the DP and masks. With n=15 the Float64Array contains 15*32768=491,520 entries, roughly 3.9 MB. The use of bitwise 1<<n is safe here because JavaScript bitwise operations are 32-bit signed, and n is at most 15.

## Common mistakes

- Treating any valid topological order as cheapest (prerequisites alone do not set cost).
- Greedily selecting the cheapest currently available next task; that may cause expensive later transitions.
- Forgetting the last task in the DP key when transition costs depend on it.
- Charging an arbitrary cost for the first task.
- Checking whether *any* predecessor is in mask, instead of **every** prerequisite.
- Using the wrong mask inclusion test: (needed[next] & mask) === needed[next].
- Ignoring duplicates/self prerequisite edges; OR handles duplicates, a self prerequisite makes the task permanently unavailable.
- Failing to return -1 when full mask is unreachable.
- Assuming switchCost[i][j] equals switchCost[j][i]; costs are directional.
- Off-by-one errors when flattening dp[mask][last] into dp[mask*n+last].

## CS61B connections

This combines directed dependency graphs, topological ordering, bit operations, and dynamic programming. A typical CS61B graph question asks for *a* topological ordering. Adding transition-dependent costs creates an optimization problem over topological orders. The DP state graph itself is a DAG ordered by growing masks, making this closely related to DAG relaxation. It is also a subset-state analogue of memoizing recursive states. Although shortest-path reasoning appears in the state-DAG interpretation, no priority queue/Dijkstra is needed.
