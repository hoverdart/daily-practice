# Attempt — One Discounted Relay Toll

Complete this before opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force / baseline complexity:
- Optimal time and space:
- Failed test, missing Python syntax, or hint needed:

## Recognition and graph modeling

- Is the original network directed? Weighted? Can it have zero-weight cycles?
- Why doesn't BFS (fewest edges) solve this?
- Why does ordinary one-distance-per-router Dijkstra lose essential information?
- Draw the expanded nodes (router, coupon_used), with coupon_used in {0, 1}.
- From (u, 0), what **two** transitions exist for each original edge u -> v of weight w?
- From (u, 1), what transition exists?
- Why is early return safe the first time Dijkstra pops the target in either layer?
- Why is the coupon optional? How are source == target and unreachable targets handled?
- Why do parallel links, zero weights, and self-loops not invalidate Dijkstra?

## Heap, proof, and CS61B

- State the Dijkstra invariant: what is final when a nonstale state is popped?
- What exactly does dist[u][used] mean?
- Write heapq.heappush / heappop syntax from memory.
- Why must I ignore stale queued pairs?
- Explain how graph expansion leads to O((n+m) log(n+m)) runtime.
- Which CS61B ideas are used: adjacency lists, relaxation, heaps, shortest-path trees?
- Describe a counterexample where a single dist[u] is insufficient.
- One idea to revisit in 2–4 days:
