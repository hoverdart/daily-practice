# Solution notes — K-Signature Window Budget

## Recognition signals

A **contiguous** subarray count, constraints **at most** K distinct and **at most** length L, and the request for **exactly** K distinct: use two monotone at-most-window counts. This is a frequency-map exercise (not a prefix-sum exercise, because validity is determined by distinct-ID cardinality).

## Brute force versus optimal

A straightforward enumeration checks all start/end pairs, building a distinct set: `O(n^2)` expected time with incremental sets and up to `O(n)` space, or worse when rebuilding each set. The optimal method computes `atMost(k,L) - atMost(k-1,L)` in two independent linear passes: expected `O(n)` time, `O(min(n,k,L))` dictionary space per pass, at most `O(n)`.

## Invariant and proof

For each right endpoint, a helper maintains the **smallest** `left` for which `[left..right]` has ≤K distinct values and length ≤L. Adding a new element can only violate these upper bounds; removing a left element cannot break them. Thus once the while loop finishes, all starts in `[left..right]` produce valid suffixes, while every earlier start violates at least one upper bound. Exactly `right-left+1` windows end at `right`.

Every nonempty window with exactly k distinct IDs is included in at-most-k but excluded from at-most-(k-1). Both counts use the **same length budget**, so their difference is exact. The helper returns zero for limit ≤0 because nonempty windows always contain at least one ID.

```text
for right, value in enumerate(data):
    frequency[value] += 1; update distinct if new
    while distinct > K or right - left + 1 > L:
        decrement frequency[data[left]], delete if zero
        left += 1
    count += right - left + 1
```

Each index enters once and exits at most once, so the apparent nested loop is amortized linear. Python dictionary operations have expected constant time.

## Common mistakes

- Counting the current window just once rather than all valid suffixes.
- Using `distinct == k` on one moving window without accounting for *multiple* starting positions.
- Forgetting to delete a key when its count reaches zero (causing wrong distinct tracking).
- Applying the length cap only after adding to the answer; using `>=` instead of `>` for a maximum inclusive length.
- Confusing maximum distinct and minimum distinct: shrinking cannot repair a *minimum* distinct requirement.
- Forgetting the `k=0` / `L=0` boundary.

**CS61B:** hash-table frequency maintenance, two pointers, cost model/amortized queue intuition, and the difference between exact and monotone predicates.
