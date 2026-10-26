# Medium — Longest Affordable Channel Window

A monitoring system receives a sequence of events. Event `i` belongs to integer channel `channels[i]` and incurs a **nonnegative** processing cost `costs[i]`.

Find the **longest contiguous, nonempty** interval `[left, right)` such that:
1. The interval contains **at most `max_types` distinct channels**, and
2. The sum of its processing costs is **at most `budget`**.

Return `(left, right)`. If multiple maximum-length intervals exist, choose the one with the **smallest left index**. If no nonempty interval is valid, return `(0, 0)`.

Implement:

~~~python
def longest_affordable_window(
    channels: list[int], costs: list[int], max_types: int, budget: int
) -> tuple[int, int]:
    ...
~~~

### Examples

- `channels=[1,2,1,3,1]`, `costs=[2,1,1,1,2]`, `max_types=2`, `budget=4` → `(0,3)` (the equally long interval `[2,5)` loses the earliest-start tie).
- `channels=[1,1,2,2,1]`, `costs=[3,1,1,1,1]`, `max_types=2`, `budget=4` → `(1,5)`.
- `channels=[9,8]`, `costs=[5,5]`, `max_types=2`, `budget=4` → `(0,0)`.

### Constraints

- `0 <= n = len(channels) = len(costs) <= 200_000`.
- Channel IDs are arbitrary integers; `0 <= costs[i] <= 10**9`.
- `0 <= max_types <= n`; `0 <= budget <= 10**15`.
- Inputs must not be mutated.
- Aim for expected O(n) time and O(n) auxiliary space in the worst case.

### Interview questions

1. Why is a window with too many distinct channels **or** too much cost repairable by moving only `left`?
2. Why would this strategy fail if processing costs could be negative?
3. How does a frequency map differ from a set when removing the leftmost event?
4. How do you maintain earliest-start tie-breaking without storing all candidate intervals?
