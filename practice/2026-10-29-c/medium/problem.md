# Medium — Shortest Distinct-Signal Coverage

A binary event stream stores sensor IDs as unsigned bytes (0–255). Find the **shortest contiguous segment containing at least `k` distinct IDs**. Return its start index and length. If several segments have minimum length, choose the **earliest start**.

```c
typedef struct { int start; int length; } Window;
Window shortest_k_types(const unsigned char *events, int n, int k);
```

If no qualifying segment exists, return `{-1, 0}`. If `k == 0`, return the empty segment `{0, 0}`, even when `n == 0`.

## Examples

- `[4,4,9,4,8,9]`, `k=3` → `{2,3}` (IDs `9,4,8`; `{3,3}` also works but starts later).
- `[0,255,0,255]`, `k=2` → `{0,2}`.
- `[7,7,7]`, `k=2` → `{-1,0}`.
- Any array with `k=0` → `{0,0}`.

## Constraints

- `0 <= n <= 200000`, `0 <= k <= 256`.
- `events` is valid for `n > 0`; IDs may include 0 and 255.
- Aim for `O(n + 256)` time and `O(256)` auxiliary space (constant-sized frequency array).
- Do not sort or modify the input.

## Interview prompts

What does `frequency[id]` count? Why do you shrink **while the window is valid** for a shortest-window objective? Why can `left` move at most `n` times total? When do you update the best answer to preserve earliest-start ties?
