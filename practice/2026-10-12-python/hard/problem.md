# Timetabled Relay Network

A packet travels through `n` directed relay stations numbered `0..n-1`. Each directed route is described by a tuple:

`(u, v, first_departure, period, travel_time)`

A vehicle from `u` to `v` departs at integer times:

`first_departure, first_departure + period, first_departure + 2 * period, ...`

Boarding takes no time. You may wait at any station for as long as needed. Traversing the route takes `travel_time` time units. You begin at station `source` at time **0**.

Return the **earliest arrival time** at `target`, or `-1` if unreachable.

## Function signature

```python
def earliest_arrival(
    n: int,
    routes: list[tuple[int, int, int, int, int]],
    source: int,
    target: int,
) -> int:
```

## Examples

**Example A**

```python
n = 4
routes = [
    (0, 1, 0, 5, 3),   # 0 -> 1, departures 0,5,10,..., ride 3
    (1, 3, 8, 5, 2),   # 1 -> 3, departures 8,13,..., ride 2
    (0, 2, 0, 1, 5),
    (2, 3, 5, 1, 6),
]
source, target = 0, 3
# Answer: 10, via 0 -> 1 (arrive 3), wait to 8, then 1 -> 3.
```

**Example B**

```python
n = 3
routes = [(0, 1, 4, 10, 2), (1, 2, 0, 3, 1), (0, 2, 0, 1, 9)]
source, target = 0, 2
# Answer: 7 (arrive at 1 at time 6, take departure 6, arrive 7).
```

## Constraints

- `1 <= n <= 100_000`; `0 <= len(routes) <= 200_000`.
- `0 <= u, v, source, target < n`.
- `0 <= first_departure <= 10**12`.
- `1 <= period <= 10**12`.
- `1 <= travel_time <= 10**12`.
- Parallel routes and self-loops are allowed. The graph is **directed**.
- Do not mutate the input.

## Goal

Aim for **O((n + m) log(n + m))** time and **O(n + m)** space with an adjacency list and a min-heap.

**Key reasoning:** Ordinary BFS ignores costs, but can Dijkstra still work when the effective cost of an edge depends on the time you reach its starting station? Explain why arriving earlier at a station cannot make your final arrival worse when waiting is allowed.
