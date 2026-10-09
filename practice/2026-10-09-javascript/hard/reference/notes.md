# Hard — Recognition and Explanation

**Recognition signals:** minimize a **maximum** edge value; at most `K` hops; graph edges with weights; monotone “can I do it if I allow threshold T?” question. This is a **binary search on the answer + BFS feasibility** problem, not a shortest-sum path.

**Brute force:** enumerate all walks with up to `K` edges and compute their maximum edge weight. Branching can be exponential. A less naive dynamic program can track the minimum peak delay per vertex for every exact hop count in `O(K E)` time, which is too slow at the full constraints.

**Optimal approach for these constraints:** binary search an integer threshold `T` in `[0,maxEdgeDelay]`. A threshold is **feasible** iff the source can reach the target using at most `K` edges with every cable delay `<=T`. Test this with BFS on the graph while ignoring edges exceeding `T`. BFS discovers vertices in nondecreasing hop count, so the first discovered hop distance is the minimum; no expanded `(vertex,hops)` state is needed for this feasibility question.

**Monotonicity:** if `T` works, any larger threshold also works (it only adds usable edges). Binary search finds the smallest feasible integer. First check feasibility at the largest weight; if false, return `-1`. If source equals target, the empty route has peak delay zero.

**Invariants:** BFS marks a vertex at **enqueue time** to avoid duplicate visits. Each queue entry has a minimum-hop distance. Do not expand vertices whose distance equals `K`. During binary search, `hi` is a known feasible threshold; `lo` is the smallest not-yet-ruled-out candidate.

**Complexity:** adjacency construction `O(V+E)`. One BFS costs `O(V+E)`; binary search over `0..W` uses `O(log(W+1))` checks, giving `O((V+E)log(W+1))` time and `O(V+E)` space. With `W=0`, one feasibility test suffices. Because cycles never improve a bottleneck route with a hop upper bound, it is safe to cap `K` at `V-1`.

**Pseudocode:**

    feasible(T):
        dist[:] = -1; dist[source]=0; queue=[source]
        while queue not empty:
            u=pop_front()
            if dist[u]==K: continue
            for (v,w) in adjacency[u]:
                if w>T or dist[v]!=-1: continue
                dist[v]=dist[u]+1
                if v==target: return true
                push_back(v)
        return false
    if source==target: return 0
    if K==0 or not feasible(maxWeight): return -1
    binary_search_smallest_T_where(feasible(T))

**Common mistakes:** summing weights instead of taking their maximum; using DFS to estimate shortest hop count; declaring a vertex visited only when dequeued; expanding at hop `K`; treating zero-weight cables as absent; failing to return `-1` when the full graph is disconnected; binary-searching without proving monotonicity; mutating input edges.

**JavaScript:** adjacency lists can be `Array.from({length:n},()=>[])`; a plain `Array` or `Int32Array` plus head/tail indices implements an `O(1)` amortized queue. Avoid `Array.shift()` inside BFS because it can be `O(n)`. A `Set` tracks visited vertices but an integer `dist` array also records hops.

**CS61B connections:** BFS and graph representations, binary-search invariants, worst-case cost, and distinction between Dijkstra's additive relaxation and this minimax feasibility formulation. A minimax Dijkstra without a hop constraint is a different problem; the hop bound matters.