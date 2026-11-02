# Explanation — Directional Rail Repairs

## Recognition signals
Grid cells are vertices, legal moves are directed edges, and each move has cost **0 or 1**. We need a minimum *sum of costs*, not a minimum number of moves. That rules out ordinary unweighted BFS. Nonnegative weights make Dijkstra valid; the special two-value weight set makes **0-1 BFS** optimal.

## Brute force versus optimal
Enumerating all routes is exponential and must handle cycles. Ordinary BFS would optimize hops rather than overrides. Dijkstra with a binary heap works in O((V+E) log V), where V=rows×cols and E≤4V.

**Optimal:** maintain `dist[r][c]` and a `deque`. When relaxing an edge of cost zero, put the new state at the **front**; when cost one, put it at the **back**. The deque orders pending distances without a comparison heap, so processing all vertices and edges takes O(V+E).

## Invariant and correctness
At every successful relaxation, `dist[v]` is the smallest route cost discovered so far. A deque's pending nonstale distances are processed in nondecreasing order: a zero-cost edge keeps the current distance and goes to the front; a one-cost edge increases it by one and goes to the back. Therefore the first nonstale removal of a vertex finalizes its shortest distance, as in Dijkstra. Early return at the goal is safe.

Stale states can arise after a better path is discovered; storing the candidate distance in the deque and skipping it if `cost != dist[r][c]` prevents redundant expansion. The cost is determined by the arrow at the **cell being left**, not the destination.

## Complexity
V=rows×cols and E≤4V. Each vertex can be relaxed only a constant number of times in 0-1 BFS (standard deque invariant); total **O(V+E)=O(rows×cols)** time and O(V) auxiliary space for distances and deque. Empty grids return zero. A simple Manhattan route costs at most V-1, so the chosen `infinity=V+1` is safe.

## Common mistakes
- Treating preferred arrows as mandatory rather than zero-cost.
- Using FIFO BFS even though edge costs differ.
- Appending zero-cost states to the back (breaks distance ordering).
- Using `grid[nr][nc]` to compute the edge cost.
- Forgetting stale-state checks when enqueuing improved distances.
- Marking a vertex visited on first **discovery** rather than relaxing shorter paths.
- Confusing 0-1 BFS with BFS over zero-weight connected components.

## CS61B connections
Adjacency lists versus implicit grid graphs, BFS/deques, Dijkstra-style relaxation, shortest-path invariants, and amortized O(V+E) analysis. A deque here plays the role of a highly specialized priority queue. This revisits the earlier low-confidence shortest-path topic with a new algorithmic constraint.