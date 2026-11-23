# Hard/stretch — Maximum Unique Rewards from Start to Exit

A directed relay network has `n` rooms. Each room `v` contains a **nonnegative** integer reward `rewards[v]`. Starting at room `start`, you may follow any directed edges, revisit rooms/edges arbitrarily often, and eventually **finish** at room `target`.

You collect a room's reward **only the first time** you visit it. You want the **maximum possible total reward** of any finite walk that ends at `target`. If no such walk exists, return `-1`.

```python
def max_collectible_value(
    rewards: list[int], edges: list[tuple[int, int]], start: int, target: int
) -> int:
    ...
```

Edges may repeat and may be self-loops. You may visit `target` before your final step, leave, and return, if the directed edges permit. A zero-reward room still counts as reachable. Do not mutate inputs.

## Examples

```python
max_collectible_value([2, 3, 5, 7], [(0,1),(1,2),(2,1),(2,3)], 0, 3)
# 17: can collect all rooms; {1,2} is a strongly connected region

max_collectible_value([1, 100, 4, 3], [(0,1),(0,2),(2,3)], 0, 3)
# 8: the 100-reward branch cannot reach the exit

max_collectible_value([5, 6], [(0,1)], 1, 0)
# -1

max_collectible_value([10, 20], [(0,1),(1,0)], 0, 0)
# 30: visit 1, then return to 0
```

## Constraints

- `1 <= n <= 150_000`, `0 <= len(edges) <= 300_000`.
- All vertex IDs are in `[0,n)`; rewards are nonnegative (possibly zero).
- The route may be very deep: **do not depend on recursive DFS** in Python.

**Target:** `O(n+m)` time and `O(n+m)` auxiliary space. Describe why the maximum reward inside a **strongly connected component** is the sum of its room rewards, why the component graph is a **DAG**, and how topological dynamic programming solves the remaining optimization.
