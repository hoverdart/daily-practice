# Longest Policy-Compliant Event Window (Medium)

A monitoring system records integer event IDs in chronological order. Each event ID has a **maximum allowed frequency inside any contiguous window**.

The dictionary `caps` overrides the per-ID limit; **unlisted IDs default to a cap of 1**. Caps are nonnegative integers, so a cap of zero forbids that event ID entirely.

Find the **longest** contiguous window in which no event ID appears more often than its cap. Return its half-open interval `(left, right)`. On equal lengths, choose the **smallest left index**. If no nonempty window is valid, return `(0, 0)`.

```python
def longest_policy_compliant_window(
    events: list[int], caps: dict[int, int]
) -> tuple[int, int]:
    ...
```

**Example**

```python
events = [1, 2, 1, 2, 1, 3, 2]
caps = {1: 2, 2: 1}
# answer: (2, 6) -> [1, 2, 1, 3]
```

**Constraints:** 0 ≤ n ≤ 200,000; event IDs may be negative; 0 ≤ cap ≤ n. Inputs must remain unchanged. Target **O(n) expected time** and O(number of distinct IDs in the active window) auxiliary space.

**Interview prompts:** Why can adding one event violate only one ID's cap? Why can the left pointer only move forward? What happens when the cap of the newly added event is zero?