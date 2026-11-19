# Medium — Longest Stable Sensor Window

A manufacturing line produces signed integer sensor readings. Choose a **contiguous** block whose highest and lowest readings differ by at most `max_spread`. Return the **longest** valid block. If multiple blocks share the maximum length, choose the one with the **smallest starting index**.

Example: `readings = [3, 8, 7, 11, 5], max_spread = 4`. The best block is `[8,7,11]` (start 1, length 3): max 11 − min 7 = 4.

## Function

```c
typedef struct {
    int start;
    int length;
} StableSpan;

StableSpan longest_stable_span(const int *readings, int n, long long max_spread);
```

## Constraints

- `0 <= n <= 200000`. `max_spread >= 0`.
- Values may be `INT_MIN` or `INT_MAX`. Cast to a wider type **before** subtracting.
- If n=0, return `{0,0}`. The input is not modified.
- Aim for O(n) time and O(n) auxiliary space, using **two index deques** tracking decreasing maxima and increasing minima.
- Return valid indices, not a copy of the block.

## Examples

- `[3,8,7,11,5], 4 -> {1,3}`
- `[1,2,3,4], 1 -> {0,2}` (earliest tie)
- `[7,7,7], 0 -> {0,3}`
- `[INT_MIN,INT_MAX], 0 -> {0,1}`
- `[], 3 -> {0,0}`

Ask yourself why max/min cannot simply be subtracted from a running scalar when the left edge moves.
