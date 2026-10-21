# Reference notes — Second Distinct Transit Cost

## Recognition signals
Directed graph, **positive weights**, minimize total travel cost, but request **second DISTINCT cost** rather than second route. This is a Dijkstra variant with **two** accepted distances per vertex. Distinct *costs* matter; multiple equal-length walks contribute only one candidate. Walks may revisit vertices, so cycles must be handled without trying to enumerate routes.

## Brute force versus optimal
Enumerating all walks is infinite when cycles are reachable. Ordinary Dijkstra keeps only `dist[v]`, which loses the second-best prefix that might lead to the second-best route to the target. A naive path enumeration or repeated DFS is exponential/infinite. Instead keep `first[v]` and `second[v]`: the two smallest **distinct** s→v walk costs. Relax both types of states through a min-heap.

## Invariant and transitions
Initialize `first[source]=0`, all other first/second distances to INF. Heap states are `(distance,vertex)`. When a state `(d,u)` is popped, ignore it unless d currently equals first[u] or second[u]. For an outgoing edge (u,v,w), let c=d+w:

1. If c < first[v], the previous first[v] becomes second[v], first[v]=c, and enqueue c. The old first was already enqueued when discovered (or processed), so it need not be enqueued twice.
2. Otherwise if first[v] < c < second[v], set second[v]=c and enqueue c.
3. If c == first[v] or c >= second[v], ignore it. Equal-cost routes are not distinct answers.

Because every edge has w>0, extending a walk strictly increases its cost. Dijkstra's heap processes viable prefixes in nondecreasing cost order; each vertex has at most two distinct finalized distance states. Any third-or-worse prefix to a vertex cannot improve the global second distinct cost when extended by the same suffix: two strictly smaller prefixes produce two strictly smaller total costs. The answer is second[target], or -1 if INF.

## Complexity
Constructing adjacency takes O(n+m) memory/time. At most two distance states per vertex are *expanded*, so at most O(m) edge relaxations occur; heap operations cost O(log(n+m)) and there may be O(m) queued candidates. Total O((n+m) log(n+m)) time and O(n+m) space. Use `long long` for accumulated cost (a 150k-edge path with cost 1e9 each is 1.5e14). The INF guard prevents overflow even if constraints are expanded later.

## Common mistakes
- Return the second *walk* popped for t even when it ties the cheapest cost.
- Keep a single distance per vertex, discarding the second-best prefix.
- Treat graph as undirected; input edges are directed.
- Forbid revisits with a Boolean visited array; the problem explicitly permits walks.
- Ignore `source==target`: the empty walk has cost zero; a positive cycle can supply the second distinct cost.
- Use int, overflow; use a max-heap by accident; forget stale-entry checks.
- Use this algorithm with negative weights (Dijkstra's ordering is invalid); zero weights require extra care in counting distinct states, so the statement restricts w>0.
- Accidentally enqueue the previous first distance twice on replacement, increasing work.

## CS61B and C++ connections
This extends CS61B edge relaxation and heap-based Dijkstra. The min-heap syntax is `priority_queue<State, vector<State>, greater<State>>` with `State=pair<long long,int>`; the default `priority_queue` is a **max**-heap. Adjacency lists `vector<vector<pair<int,long long>>>` are O(n+m), unlike an O(n²) matrix. `auto [d,u]` is C++17 structured binding. Compare with BFS for unit edges, 0–1 BFS for weights 0/1, and Bellman-Ford for negative edges. Here the graph *state* is conceptually (vertex, rank 1 or 2); unlike keycard BFS, the ranks summarize the two distinct best costs, not inventory masks.
