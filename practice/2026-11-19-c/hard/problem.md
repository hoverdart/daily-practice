# Hard / Stretch — Fewest Turns for a Grid Relay

A remote relay robot travels in a rectangular grid from the upper-left cell to the lower-right cell. `'.'` means passable and `'#'` blocked. It may move one cell up/down/left/right per step; it may revisit cells. It pays **one unit for changing direction between consecutive moves**, and **zero for continuing straight**. The *first* move in any direction is free. Find the minimum number of turns, or -1 if unreachable.

A minimum-step BFS is **not** automatically a minimum-turns search. The same cell reached facing different directions is a different future state.

## Function

```c
int min_relay_turns(const char *const *grid, int rows, int cols);
```

Return the minimum turns or -1 if there is no route (including empty dimensions or blocked source/destination). Grid characters are only `'.'` and `'#'`. Input is not modified.

## Constraints

- `1 <= rows, cols` and `rows * cols <= 200000` for nonempty grids.
- Grid rows are NUL-terminated C strings of length `cols`.
- Aim for O(rows × cols) time and O(rows × cols) extra space.
- Implement a **0–1 BFS** with an explicitly managed double-ended queue in C. Every state is `(r,c,last_direction)`. Continuing in the same direction costs 0, turning costs 1.
- Initialize all four directional states of the starting cell to distance zero so the first physical movement is free. A 1×1 open grid needs zero turns.
- Do not allocate the full O((RC)²) graph: generate up to four neighbors as needed.

## Examples

```text
grid = ["..."]                      -> 0
grid = ["..",".."]                 -> 1
grid = ["..#", "#..", "##."]        -> 3
grid = [".#","##"]                 -> -1
grid = ["."]                       -> 0
grid = ["#"]                       -> -1
```

Your solution must work for a very long 1×200000 corridor without recursion or a fixed-size queue that overflows on repeated relaxations. Think carefully about deque ownership, growth, and stale queued distances.
