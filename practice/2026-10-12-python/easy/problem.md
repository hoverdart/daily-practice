# First Unique Alert Stream

A monitoring service receives integer alert IDs one at a time. After **every** arrival, report the **earliest-arriving ID that has occurred exactly once in the entire prefix seen so far**. If there is no such ID, report `None`.

The output has the same length as the input. IDs can be negative. An ID that repeats is never unique again, even if other IDs arrive later.

## Function signature

```python
def first_unique_after_each(events: list[int]) -> list[int | None]:
```

## Examples

- `[7, 2, 7, 3, 2, 3]` → `[7, 7, 2, 2, 3, None]`
- `[4, 4, 5, 5, 6]` → `[4, None, 5, None, 6]`
- `[-2, -1, -2, -1]` → `[-2, -2, -1, None]`
- `[]` → `[]`

## Constraints

- `0 <= len(events) <= 200_000`.
- `-10**9 <= events[i] <= 10**9`.
- Do not mutate `events`.

## Goal

Expected **O(n)** total time and **O(n)** auxiliary space. In your explanation, justify why repeated queue removals do **not** make the algorithm quadratic.

**Recognition question:** You already know how to count occurrences with a hash map. What additional data structure keeps the earliest still-valid candidate at the front?
