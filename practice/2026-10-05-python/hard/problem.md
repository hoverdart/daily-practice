# Battery-Aware Relay Route

A fleet controller routes a packet through `n` relay stations numbered `0..n-1`. Each undirected link `(u, v, cost)` consumes a positive integer amount of battery.

The packet carries a one-use **efficiency token**. On at most one traversed link, it may reduce that link's cost to `cost // 2`. The token may remain unused.

Return the minimum battery cost from station `0` to station `n-1`, or `-1` if unreachable.

## Signature
```python
def min_battery_cost(n: int, edges: list[tuple[int, int, int]]) -> int:
```

## Examples
- `n=4, edges=[(0,1,8),(1,3,8),(0,2,5),(2,3,20)]` → `12`
- `n=3, edges=[(0,1,3),(1,2,3),(0,2,10)]` → `4`
- `n=1, edges=[]` → `0`
- `n=3, edges=[(0,1,2)]` → `-1`

## Constraints
- `1 <= n <= 100_000`
- `0 <= len(edges) <= 200_000`
- `0 <= u,v < n`
- `1 <= cost <= 10^9`
- Parallel edges are allowed.

## Complexity goal
Aim for **O((n + m) log n)** time and **O(n + m)** space.
