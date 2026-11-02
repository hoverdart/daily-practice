# Directional Rail Repairs (Hard / Stretch)

A rectangular rail yard has a one-way **preferred direction** painted on each cell. A maintenance robot starts at the top-left cell and must reach the bottom-right cell. It may move to any orthogonally adjacent cell that stays inside the yard.

Leaving a cell in its preferred direction costs **0 repairs**. Leaving it in any of the other three directions costs **1 repair** (an override). You may revisit cells, but you want the minimum total number of overrides.

Each grid entry is an integer direction:

| Code | Direction | Change (row, col) |
|---|---|---|
| 0 | up | (-1, 0) |
| 1 | right | (0, +1) |
| 2 | down | (+1, 0) |
| 3 | left | (0, -1) |

Implement:

```python
def min_direction_overrides(grid: list[list[int]]) -> int:
    ...
```

Return the minimum repair count. An empty grid returns 0. For a single cell, start equals goal, so return 0. All nonempty grids are rectangular, and every entry is in `{0,1,2,3}`. Do not mutate the input.

**Examples**

```python
grid = [[1, 1, 1],
        [1, 1, 1]]
# 1: move right for free, then override once to go down

grid = [[2, 3],
        [1, 0]]
# 0: down, then right (both preferred)
```

**Constraints:** Up to 200,000 cells total. Aim for **O(rows × cols)** time and space.

**Interview prompts:** Why is ordinary BFS incorrect? Why is Dijkstra correct but unnecessarily heavy? How does a deque simulate a priority queue when all edge costs are either zero or one?