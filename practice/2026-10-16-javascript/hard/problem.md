# Hard / Stretch — Keycard Escape Maze

A factory security map is a rectangular grid of strings. Each step moves one cell **up, down, left, or right** and costs 1. Find the minimum number of steps from `S` to `E`, or return `-1` if impossible.

Cells:
- `S` start, `E` exit, `.` floor, `#` wall.
- `a`, `b`, `c`, `d` are keycards. Stepping onto one **permanently collects** it.
- `A`, `B`, `C`, `D` are doors; you may enter a door only after collecting its matching lowercase keycard.
- A key may be reused any number of times. You may revisit cells. The grid is not modified.

Implement:

```js
function shortestKeycardEscape(grid) // minimum steps or -1
```

**Examples**

```js
["SE"]                  // 1
["SAE"]                 // -1: A is locked and no a exists
["#a##", "S.AE", "####"] // 5: must return through (1,1) with the key
```

**Constraints:** `1 <= rows, cols <= 30`; grid rectangular, contains exactly one `S` and one `E`; only symbols listed above. Not every key or door must appear.

**Target:** O(rows × cols × 2^4) time and space (constant four directions). Explain why `visited[row][col]` alone is wrong, why BFS is sufficient rather than Dijkstra, and when to mark a state visited.
