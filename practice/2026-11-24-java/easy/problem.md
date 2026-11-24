# Easy — Previous Higher Priority

A monitoring system receives events in chronological order. Each event has a signed integer priority. For every event, report the index of the most recent **earlier** event whose priority is **strictly greater** than its own, or -1 if none exists.

Implement:
```java
public static int[] previousHigher(int[] priority)
```

Return a new array of equal length; indices are zero-based. Do not modify the input. Equal priorities do not qualify, even when adjacent.

## Examples

- [8, 3, 3, 5, 2, 8] -> [-1, 0, 0, 0, 3, -1]. For index 4 (priority 2), index 3 is closer than index 0.
- [4, 4, 4] -> [-1, -1, -1].
- [7, 5, 2] -> [-1, 0, 1].
- [] -> [].

## Constraints

- 0 <= n <= 200,000.
- Priorities may be any Java int.
- Input is non-null.
- Aim for O(n) time, without scanning backward independently for each event.
