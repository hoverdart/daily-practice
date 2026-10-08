# Hard Reference Notes — Hazard-Budget Courier

**Read after attempting the problem.**

## Recognition signals

Directed weighted graph + minimum total time + nonnegative edge times => Dijkstra. But "risk budget" means the best arrival at depot `u` depends on how much budget remains. **Physical node alone is not the full state.**

## Wrong / brute approaches

- DFS enumerate all paths: exponential with cycles; requires pruning and still impractical.
- Plain Dijkstra with `dist[u]`: incorrect. A fast-but-risky arrival may prevent finishing, while a slower low-risk arrival remains feasible.
- Bellman-Ford on expanded states: correct but O((nB)(mB)) if implemented naively; useful as a small-input test oracle.

## State expansion

Define `state=(u,spent)` for depot `u` and total hazard already spent `spent` in 0..budget. Encode as:

    state_id = u * (budget+1) + spent

For road `u -> v` with time `t` and hazard `r`, an expanded edge exists only when `spent+r <= budget`:

    (u,spent) -> (v,spent+r), cost t

There are `V' = n*(budget+1)` states and at most `E' = m*(budget+1)` expanded edges.

## Dijkstra invariant

`dist[state]` is the best known travel time to that **exact** state. The min-heap contains candidate pairs `(time,state)`. Pop the minimum; if its time differs from `dist[state]`, it is stale and can be ignored. Because all edge times are nonnegative, the first non-stale target state popped has the global optimal feasible travel time.

Pseudo:

    dist[*] = INF
    dist[(0,0)] = 0
    heap.push((0,(0,0)))
    while heap not empty:
      (d,(u,spent)) = heap.pop_min()
      if d != dist[u,spent]: continue
      if u == n-1: return d
      for each directed edge (u,v,time,risk):
        if spent+risk > budget: continue
        next = (v,spent+risk)
        if d+time < dist[next]:
          dist[next] = d+time
          heap.push((dist[next],next))
    return -1

## Binary heap in C

C has no standard `priority_queue`. Use an array of `HeapNode { long long time; int state; }`. A **1-based** heap simplifies parent `i/2` and children `2*i`, `2*i+1`. `heap_push` swims the new item up; `heap_pop` replaces root with last item and sinks it. Each O(log heap_size).

The reference allocates enough heap capacity for at most `1 + E'` pushes: each expanded edge is relaxed only when its source state is finalized, and strict improvements add at most one push per edge traversal. Stale entries do not expand outgoing edges. A dynamically resized heap is also valid.

## Complexity

With `B=budget+1`: O((nB + mB) log(mB+2)) time (heap implementation with duplicate candidates), O(nB + mB) memory for distances, adjacency links, and heap. With `n=1`, the source is already the destination, answer 0.

## Common mistakes

- Using `int` for total time: a path of three 1e9-time edges is 3e9.
- Treating roads as undirected: only `from -> to` exists.
- Marking a depot visited once regardless of spent hazard.
- Enqueuing edges that exceed the remaining budget.
- Forgetting stale heap entries after a better distance is discovered.
- Accidentally using a **max** heap or comparing state ID instead of time.
- Leaking `head`, `next`, `dist`, or heap storage on early return.
- Zero-time/zero-risk cycles are safe with strict `candidate < dist[next]`.

## CS61B connection

Binary heap swim/sink, adjacency-list graphs, shortest-path edge relaxation, and graph-state modeling. Compare this with the earlier half-price transit problem: both require an expanded state, but this one tracks a **bounded resource** rather than a binary coupon-used flag.

## Next time, recognize

If reaching the same physical vertex with different resources changes future options, treat **(vertex, resource)** as the graph vertex.
