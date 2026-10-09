# Easy — Recognition and Explanation

**Recognition signals:** sorted/nondecreasing data; “first index satisfying a condition”; duplicates; `>=` boundary. This is **lower_bound**, not ordinary “find any matching element.”

**Brute force:** scan from left to right and return the first qualifying index, `O(n)` time and `O(1)` space. It works but ignores sortedness.

**Optimal idea:** maintain a half-open interval `[lo,hi)` that contains the insertion position (which may equal `n`). At `mid`, if `loads[mid] >= limit`, the answer could be `mid` or to its left, so set `hi=mid`. Otherwise everything through `mid` fails, so set `lo=mid+1`. Stop when `lo===hi`; `n` means no qualifying index.

**Invariant:** all indices below `lo` are known to fail, and all indices at/above `hi` (when in bounds) are known to satisfy the predicate. The unknown boundary stays in `[lo,hi]`.

**Complexity:** `O(log(n+1))` time for nonempty input (conventionally `O(log n)`), `O(1)` extra space.

**Common mistakes:** returning immediately when `loads[mid]===limit` (not necessarily the first); using `hi=n-1` with half-open logic; infinite loops from failing to advance `lo`; missing empty/no-match cases; using `(lo+hi)/2` without flooring in JavaScript.

**Pseudocode:**

    lo=0; hi=n
    while lo<hi:
        mid=floor((lo+hi)/2)
        if loads[mid]>=limit: hi=mid
        else: lo=mid+1
    return -1 if lo==n else lo

**CS61B connection:** binary search loop invariants and worst-case logarithmic cost. In JavaScript use `Math.floor`; array indexing returns `undefined` outside bounds, so never rely on it for sentinel comparisons.