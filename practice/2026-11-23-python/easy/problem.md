# Easy — Closest Repair Hub by Hops

An undirected network of `n` workstations is numbered `0` through `n-1`. Each undirected link takes exactly **one hop**. Several workstations host a repair hub. For **every** workstation, return the fewest number of links needed to reach *any* repair hub.

Write:

```python
def nearest_repair_hops(n: int, links: list[tuple[int, int]], hubs: list[int]) -> list[int]:
    ...
```

Return an array of length `n`. A hub has distance `0`. Return `-1` for a workstation that cannot reach any hub. You may traverse links in either direction. Repeated links, self-links, and repeated hub IDs are permitted and must not change the result. Do not mutate the input. For `n=0`, the answer is `[]`.

## Examples

```python
nearest_repair_hops(6, [(0,1),(1,2),(2,3),(4,5)], [0,5])
# [0,1,2,3,1,0]

nearest_repair_hops(4, [(0,1),(2,3)], [])
# [-1,-1,-1,-1]

nearest_repair_hops(5, [(0,1),(1,2),(2,3),(3,4)], [0,4])
# [0,1,2,1,0]
```

## Constraints

- `0 <= n <= 200_000`; every endpoint and hub ID is a valid vertex.
- `0 <= len(links) <= 300_000`; the graph may be disconnected.
- Memory budget is proportional to network size.

**Target:** `O(n + m + h)` time and `O(n + m)` auxiliary space for `m` links and `h` hub entries. Explain why one queue seeded with all hubs is better than running one search per hub.
