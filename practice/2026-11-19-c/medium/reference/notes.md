# Reference Notes — Longest Stable Sensor Window

## Recognition signals

“Longest **contiguous** region” plus a condition that cannot become worse when removing elements ⇒ sliding window. But `max(window)-min(window)` requires fast eviction of expired extrema. Two **monotonic deques** provide the maximum and minimum in O(1) amortized time per advance. No sorting: sorting would destroy contiguity.

## Brute force versus optimal

Enumerate all starts and ends, maintain a running min and max for each fixed start; compare every valid range. O(n²) time and O(1) space. A heap per extreme with delayed deletion gives O(n log n) time but more bookkeeping. Optimal: maintain two deques of *indices* in the current window, maximum values decreasing and minimum values increasing. Adding a new value discards all strictly weaker or equal indices from the back, because the new index is at least as useful as a prior equal extreme and expires later. Pop expired indices from the front when moving left.

## Core invariant

After each right insertion, the max deque stores candidate indices in increasing index order and decreasing value order; the min deque stores candidate indices in increasing index order and increasing value order. Therefore their fronts identify the exact extreme in [left,right]. While the spread exceeds the budget, increase left and evict expired front indices; once valid, **the smallest feasible left for the current right** has been reached. No smaller left could be valid because it would contain the invalid prior window. Thus this is the longest valid suffix ending at right; checking all right indices finds the global longest interval.

## Complexity

Each index is pushed once and popped at most once from each deque. Despite two nested while loops, total work is O(n), auxiliary memory O(n) in the worst case. For an empty input, immediately return (0,0). Use 64-bit promotion **before** subtraction: `INT_MAX - INT_MIN` does not fit `int`. Allocations are freed on all ordinary returns.

## Common mistakes

- Storing **values** instead of indices makes it impossible to expire an old extreme correctly.
- Testing spread using signed int subtraction invokes overflow for extreme readings.
- Removing only one item from the left when the window is still invalid.
- Updating best *before* repairing an invalid window.
- Accidentally preferring the *later* start in an equal-length tie.
- Confusing queue head and tail after dropping dominated candidates. Each tail is bounded by number of insertions, so a length-n index array suffices.

## CS61B connections

Array-backed deque indices, amortized analysis, monotonic data structures, interval invariants, and the sliding-window template. Contrast the November 12 drift problem: there the window's **sum of adjacent edge costs** could be updated with scalar addition/subtraction; here max/min cannot, which is why the deque choice matters.

## Pseudocode

```text
for right in [0,n):
    remove max-deque back while value <= new value; push right
    remove min-deque back while value >= new value; push right
    while max(front)-min(front) > budget:
        pop front indices equal to left
        left++
    update best using [left,right], earliest start on ties
```
