# Easy — First Saturated Checkpoint

A monitoring system stores a **nondecreasing** array `loads`, where `loads[i]` is the cumulative number of packages processed by checkpoint `i`. Find the **first index** whose load is **at least** `limit`. Return `-1` if no checkpoint qualifies.

Implement:

```js
function firstCapacityIndex(loads, limit) { /* ... */ }
```

Examples:
- `loads=[1,3,3,8,11], limit=3` → `1` (the first of two equal values).
- `loads=[1,3,3,8,11], limit=9` → `4`.
- `loads=[2,2,2], limit=1` → `0`.
- `loads=[], limit=0` → `-1`.

Constraints: `0 <= loads.length <= 200000`; values and `limit` are safe integers; `loads` is sorted nondecreasing. **Target:** `O(log n)` time, `O(1)` extra space. Do not mutate the input.

**Before coding:** Explain why returning on the first equality found by binary search can produce the wrong index.

**CS61B:** binary search invariants, half-open intervals, asymptotic analysis, duplicate keys.