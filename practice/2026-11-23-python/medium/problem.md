# Medium — K-Signature Window Budget

A telemetry timeline contains integer signature IDs, including possible negative IDs. A **window** is any nonempty contiguous slice. A valid window:

1. contains **exactly `k` distinct signature IDs**; and
2. has length **at most `max_length`**.

Return the total number of valid windows (not just the longest window). Overlapping windows count separately.

```python
def count_signature_windows(signatures: list[int], k: int, max_length: int) -> int:
    ...
```

For `k <= 0`, `max_length <= 0`, or empty input, return 0. Do not modify the input. The answer may exceed a 32-bit integer (Python integers do not overflow).

## Examples

```python
count_signature_windows([2, 1, 2, 3], 2, 3)  # 4
# [2,1], [2,1,2], [1,2], [2,3]

count_signature_windows([7, 7, 7], 1, 2)     # 5
count_signature_windows([1, 2, 1], 2, 1)     # 0
count_signature_windows([-1, 2, -1], 2, 3)  # 3
```

## Constraints

- `0 <= len(signatures) <= 200_000`.
- IDs are arbitrary integers; `k` and `max_length` may exceed `n`.

**Target:** expected `O(n)` time with `O(n)` worst-case auxiliary space. The intended approach maintains frequencies in sliding windows and converts **exactly k** into the difference of two **at-most** counts. Explain why both the distinct-count ceiling and maximum-length ceiling must be maintained before adding to the count.
