# Medium — Longest Compatible Batch

A conveyor produces a sequence of integer product labels `tags`. A calibration mode can handle **at most `k` distinct labels** in one uninterrupted batch. Return the **starting index and length** of the longest contiguous compatible batch as `[start, length]`. On equal lengths, prefer the **earliest start**.

Implement:

```js
function longestCompatibleBatch(tags, k) { /* ... */ }
```

Examples:
- `tags=[2,3,2,1,1,4], k=2` → `[0,3]` (earliest length-3 window).
- `tags=[1,2,1,3,4,3,3], k=2` → `[3,4]` (window `[3,4,3,3]`).
- `tags=[7,7,8], k=1` → `[0,2]`.
- `tags=[7,8], k=0` → `[0,0]`.

Constraints: `0 <= tags.length <= 200000`; labels are safe integers (may be negative); `0 <= k <= 200000`. Return `[0,0]` for an empty array or `k=0`. Do not mutate input.

**Target:** `O(n)` time, `O(min(n,k+1))` auxiliary space. No sorting.

**Before coding:** Explain what the frequency map counts, when a label must be deleted from it, and why the nested shrinking loop is still linear overall.

**CS61B:** hash maps and amortized pointer movement, invariants, JavaScript `Map` API.