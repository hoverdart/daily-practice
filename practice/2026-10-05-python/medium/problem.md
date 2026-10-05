# Stable Sensor Window

A machine emits a sequence of integer sensor codes. A contiguous interval is **stable** if it contains at most `k` distinct codes.

Return the length of the longest stable contiguous interval.

## Signature

```python
def longest_stable_window(readings: list[int], k: int) -> int:
```

## Examples

- `readings=[1, 2, 1, 2, 3], k=2` → `4`
- `readings=[4, 4, 4], k=1` → `3`
- `readings=[1, 2, 3], k=1` → `1`
- `readings=[], k=3` → `0`

## Constraints

- `0 <= len(readings) <= 200_000`
- `0 <= k <= 200_000`
- Codes may be negative.
- If `k == 0`, the answer is 0.

## Complexity goal

Aim for **O(n)** time and **O(k)** space (or O(number of distinct values in the active window)).
