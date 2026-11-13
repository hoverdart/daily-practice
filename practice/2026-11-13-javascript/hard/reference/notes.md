# Hard reference — Alternating-Band Relay Route

## Recognition signals

Weighted shortest paths plus an **allowed-next-action rule dependent on the previous edge** indicate a **state-space graph**. One shortest distance per physical station is insufficient: arriving cheaply on band 0 cannot use an outgoing band-0 link, whereas a more expensive band-1 arrival can.

## Brute force → optimal

Enumerating routes can be exponential or nonterminating with cycles. A sound comparison algorithm is **Bellman-Ford** on 2n expanded states: for each physical link `(u,v,w,b)`, add transition `(u,1-b) -> (v,b)`. Initialize both source states at zero. Relax up to 2n-1 passes, for **O(nm)** time (on expanded graph) and O(n+m) storage if edges/adjacency are materialized. It handles the nonnegative weights here but is too slow.

Use **Dijkstra** since all delays are nonnegative. Create two states per station: `(u,0)` and `(u,1)`, where the second value is the most recently used band. Encode as `2*u+band`. For each edge `[u,v,w,b]`, relax only from `(u,1-b)` to `(v,b)`, adding cost w. Initialize **both** source band states to distance 0, which allows either first edge. Return 0 immediately when source==target.

## Core invariants / proof

Every valid original route corresponds to an expanded-graph path from an initialized source state, and every such expanded path represents an alternating-band route. The transformation preserves costs, so their shortest costs coincide. For nonnegative edges, when the min-heap pops a non-stale minimum tentative distance, Dijkstra has established the optimal distance to that expanded state. Therefore the first non-stale popped state at the physical target has the minimum over both possible terminal bands.

**Min-heap invariant:** a parent's priority (cost) is no larger than either child's. `push` swims upward; `pop` replaces the root by the last item then sinks downward; both take logarithmic time. With lazy inserts instead of decrease-key, skip outdated pairs using `if(cost !== dist[state]) continue`. Strict improvements prevent infinite inserts on zero-cost cycles.

## Runtime / space

The state graph has 2n vertices and at most m legal transitions. Building adjacency takes O(n+m), distances O(n). Heap can hold O(m) records due to lazy duplicate entries; at most O(n+m) successful pushes. **O((n+m)log(n+m)) time** and **O(n+m) space**. The biggest finite cost under given bounds is far less than JS's safe integer ceiling.

## Common mistakes

One distance per physical vertex; forcing first band 0; allowing equal consecutive bands; treating directed links as undirected; using a max-heap; marking a vertex settled when pushed; not skipping stale heap entries; BFS on unequal weights; negative weights with Dijkstra; zero-length source=target; self-loops and duplicate directed edges; mutating input.

## CS61B connections

Directed adjacency lists, Dijkstra's relaxation invariant, min-heap swim/sink, priority queues, and V/E complexity analysis. State expansion also appears in grid-with-keys BFS and constrained routes, but here the extra state is the **last link's band**, not a one-time coupon.
