# Reference Notes — Timetabled Relay Network

## Recognition signals
A directed graph, nonnegative travel/wait times, and a request for the **earliest arrival** suggests shortest paths with a priority queue. The twist is that an edge's effective waiting time depends on when you arrive. This is a **FIFO time-dependent shortest-path problem**, not ordinary constant-weight Dijkstra, BFS, or a coupon-style state expansion.

## Brute force → optimal
For small integer times, expand the state to `(station, time)` and simulate waiting one unit or taking a route that departs at exactly that time. This is what the tests' independent slow oracle does. It is not feasible for timestamps up to 10^12: the time dimension explodes.

Instead, keep one best known earliest-arrival time `dist[u]` per station. Build a directed adjacency list and pop the station with the smallest tentative arrival time from a min-heap. For each outgoing route, compute the **first departure at or after** `time`:

```python
if time <= first:
    departure = first
else:
    departure = first + ((time - first + period - 1) // period) * period
candidate = departure + travel
```

The integer expression `(a + b - 1) // b` computes `ceil(a / b)` for nonnegative integers. If `candidate < dist[v]`, relax `dist[v]` and push the new pair. Skip popped entries for which `time != dist[u]`. Return when the target is popped as the current best; otherwise -1.

## Why Dijkstra is valid here
For each route, the arrival function `A(t) = next_departure_at_or_after(t) + travel` is **nondecreasing**: arriving later at the departure station cannot catch an earlier vehicle. Because waiting is allowed, arriving earlier at a station always permits simulating any later arrival's choices. This is the **FIFO property**. The minimum-heap extraction of the smallest tentative arrival is therefore safe: no path through a not-yet-settled later-arrival state can improve it. With no negative time travel, the standard label-setting proof applies.

**Important limitation:** Time-dependent Dijkstra can fail when waiting is forbidden and later arrival could be advantageous, when edge arrival functions violate FIFO, or when the true state also depends on something besides current station and time (e.g., tickets consumed).

## Complexity
Constructing the adjacency list: O(n+m) time/space. Each successful relaxation inserts one heap item, at most O(m) total, and each pop is O(log(m+1)). Overall **O((n+m) log(n+m))** time, **O(n+m)** space for adjacency lists, distances, and heap. A more precise bound is O(n+m log(m+1)); the stated bound is a safe conventional upper bound.

## Common mistakes
- Use `time + travel` without waiting for the next departure.
- Use floor division where ceiling division is required.
- Treat routes as undirected or forget parallel routes.
- Greedily choose the next departing edge instead of the globally earliest arrival.
- Mark a station visited on **push** rather than on a final heap **pop**.
- Omit the stale-entry check; correctness may survive but efficiency degrades.
- Accidentally use a max-heap, or confuse `heappop` with `heappush`.
- Use floats to compute the ceiling; large timestamps lose precision. Keep arithmetic integral.

## CS61B connections
Adjacency lists, priority queues (binary heaps), and edge relaxation are the same foundations as ordinary Dijkstra. This version changes only the relaxation formula. Compare it to the October 5 shortest-path attempt (confidence 1/5) and October 7's unfilled Dijkstra practice: the goal is automatic recall of the **heap → stale check → outgoing edges → relax → push** pattern, while reasoning about a new FIFO invariant.
