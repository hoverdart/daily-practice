# Solution notes — Closest Repair Hub by Hops

## Recognition signals

Undirected **unweighted** graph, minimum number of **hops**, and multiple equally valid origins: this is **multi-source BFS**. No priority queue is needed. A zero-length path gives distance 0 at a hub.

## Baseline versus optimal

The obvious baseline runs BFS separately from each workstation until reaching any hub: `O(n(n+m))` time in the worst case (or run BFS from each hub with similarly wasteful repeats), with `O(n+m)` space. Multi-source BFS starts with *all* hubs already discovered, producing each vertex's minimum distance to the nearest source in one pass: `O(n+m+h)` time, `O(n+m)` auxiliary space, including graph and queue.

## Queue invariant / correctness

All items are enqueued in nondecreasing distance. Initially every distinct hub is enqueued with distance 0. When popping a vertex at distance `d`, each previously unseen neighbor is assigned `d+1`. All paths using fewer than `d+1` links would have passed through a vertex popped earlier, so first discovery is optimal. Mark on enqueue to avoid repeated tickets. A missing hub or unreachable component stays `-1`.

```text
for u in hubs: distance[u]=0; queue.push(u)  # once per distinct u
while queue:
    u = queue.popleft()
    for v in graph[u]:
        if distance[v] == -1:
            distance[v] = distance[u] + 1
            queue.append(v)
```

## Common mistakes

- Running one BFS per hub/workstation instead of seeding a single queue.
- Using a LIFO list or `pop()` instead of FIFO `deque.popleft()`.
- Assigning distance only on dequeue, causing duplicate enqueues and incorrect queue invariants.
- Forgetting isolated vertices, the empty-hub case, or treating parallel/self links specially when no special handling is needed.
- Using this BFS for weighted links, where Dijkstra is appropriate if weights are nonnegative.

**CS61B:** adjacency lists, visited/dist arrays, BFS frontier layers, deque runtime, and shortest-path algorithm selection.
