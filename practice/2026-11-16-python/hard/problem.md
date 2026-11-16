# Hard / Stretch — Farthest Critical Server in a Tree

A distributed service runs on **n servers** connected by exactly n−1 undirected links. Every pair is connected by a unique simple route. Link i is a triple **(u, v, w)** with nonnegative travel latency w. A subset of servers is designated **critical**.

For **every** server u, report the greatest total latency along the unique route from u to **any critical server**. If there are no critical servers, return a list of n values all equal to −1. A critical server counts as distance 0 from itself; duplicate entries in the critical list do not change the answer.

**Do not run a separate graph search from each critical server.** The target complexity is O(n).

## Signature

~~~python
def farthest_critical_distances(
    n: int, edges: list[tuple[int, int, int]], critical: list[int]
) -> list[int]:
    ...
~~~

**Constraints:** 1 ≤ n ≤ 150,000; len(edges)=n−1; edges form a valid undirected tree; 0 ≤ w ≤ 10^6; 0 ≤ critical[i] < n. Return integers (path totals can exceed 32-bit range).

## Examples

~~~python
farthest_critical_distances(
    4, [(0, 1, 2), (1, 2, 3), (1, 3, 4)], [0, 2]
)
# [5, 3, 5, 7]

farthest_critical_distances(3, [(0, 1, 1), (1, 2, 8)], [1])
# [1, 0, 8]

farthest_critical_distances(2, [(0, 1, 9)], [])
# [-1, -1]
~~~

## Requirements

1. Build an adjacency list and root the tree at server 0.
2. Use an **iterative** traversal to avoid Python recursion-depth failures on a long chain.
3. In a bottom-up pass, calculate the farthest critical distance within each node's own subtree (**down**).
4. In a top-down pass, calculate the farthest critical distance coming from outside that subtree (**up**). For a child, its parent's best path must **not** reuse that same child's subtree.
5. Return max(down[u], up[u]) per node.

Explain the naive O(n × number_of_critical_servers) multi-search approach, and why keeping the two best child contributions at each parent is enough to exclude one particular child in O(1).
