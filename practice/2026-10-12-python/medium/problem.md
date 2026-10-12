# Exactly K Event Types

An audit log is a sequence of integer event codes. Count how many **nonempty contiguous subarrays** contain **exactly `k` distinct event codes**.

Two subarrays with the same values but different index ranges count separately. Codes may be negative.

## Function signature

```python
def count_exactly_k(events: list[int], k: int) -> int:
```

## Examples

- `events=[1, 2, 1, 2, 3], k=2` → `7`
- `events=[1, 1, 1], k=1` → `6`
- `events=[1, 2, 3], k=2` → `2`
- `events=[-1, -2, -1], k=2` → `3`
- `events=[], k=2` → `0`
- `events=[1, 2], k=0` → `0`

## Constraints

- `0 <= len(events) <= 200_000`.
- `0 <= k <= 200_000`.
- `-10**9 <= events[i] <= 10**9`.
- The answer may be as large as `n * (n + 1) // 2`.
- Do not mutate `events`.

## Goal

Expected **O(n)** time and **O(min(n, k))** auxiliary space for `k >= 1` (O(n) is an acceptable bound).

**Recognition question:** A window with *at most* K distinct values has a monotone validity condition. How can two "at most" counts give the number with **exactly** K distinct values?
