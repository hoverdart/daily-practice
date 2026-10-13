# Reference notes — Minimum Calibration Segment

## Recognition signals

Look for **shortest contiguous subarray** satisfying a monotone condition: adding more events cannot invalidate quota satisfaction. This strongly suggests a variable-length sliding window, rather than a set or prefix sum alone. Because the problem requires multiplicities, use a frequency map, not merely a set.

## Brute force versus optimal

Enumerate every start/end pair, count events in each candidate window, and check each quota: O(n^2 k) if counts are recomputed, or O(n^2 + nk) with incremental counts per start. Both are too slow at n=100,000.

Use two pointers left and right, a map need[id] holding each quota, and have[id] holding counts **only for required IDs** in the current window. Maintain missing = the total number of still-unfulfilled required *occurrences*, not the number of distinct IDs.

When adding value x on the right, increment have[x] only if x is required. If its new count is <= need[x], decrement missing; extra copies do not help. When removing x from the left, if its old count was <= need[x], increment missing; otherwise that removed copy was surplus.

After expanding right, repeatedly shrink from left while missing==0. Record a candidate before each removal; if removal makes missing positive, the next right expansion is required. Strictly update only on shorter length so the first (smallest-left) minimum-length window wins.

## Invariant and proof

The window [left,right] has precisely the have frequencies. missing equals sum over required IDs of max(0, need[id]-have[id]). Thus missing==0 iff all quotas are met. For a fixed right endpoint, shrinking to the first invalid window examines every possible valid left endpoint ending at right; the shortest one is the last valid window examined. Because both pointers only increase, each event enters and leaves the window at most once.

## Complexity

Building need takes O(k). Each event is added once and removed at most once, with expected O(1) HashMap operations: **O(n+k) expected time**, O(k) auxiliary space. The nested while loop is amortized O(n), not quadratic.

## Common mistakes

- Treating missing as distinct unsatisfied types but decrementing it on every matched event.
- Decrementing missing for surplus copies, making it negative.
- Failing to increment missing when removing a needed copy.
- Forgetting that negative IDs are valid map keys.
- Keeping counts for every unrelated event: unnecessary memory.
- Returning window length rather than inclusive [left,right].
- Using <= for tie updates and accidentally preferring a later start.
- Forgetting the impossible [-1,-1] case.

## CS61B connections

HashMap frequency accounting, array indexing, amortized two-pointer analysis, and the distinction between a set (presence) and a map (multiplicity).

## Java syntax

```java
Map<Integer, Integer> need = new HashMap<>();
int count = have.getOrDefault(x, 0) + 1;
have.put(x, count);
if (count == 1) have.remove(x); // only when removing the final copy
```

Think of the map as a live summary of the current interval, not a history of everything seen.
