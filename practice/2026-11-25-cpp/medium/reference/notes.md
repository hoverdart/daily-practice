# Longest Calibration Span — solution notes

## Recognition signals
"Longest contiguous," a nonnegative budget, and a single free reading suggest a variable sliding window. The best waiver is the maximum cost. We need both the sum and an exact dynamic maximum, so a frequency map alone is not enough.

## Brute force to optimal
Enumerating all spans and recomputing sums/maxima costs O(n³). Updating sum and max as each right boundary grows for each left gives O(n²), O(1) space. A multiset plus running sum supports a sliding window in O(n log n) time. A monotonic deque improves this to O(n).

## Why sliding works
Define F(W)=sum(W)-max(W), with F(empty)=0. Adding x to a nonempty W with maximum M changes F by min(x,M), which is nonnegative. Removing an element therefore never raises F. Once [left,right] is invalid, every later extension with that same left is invalid. Removing left until valid finds the earliest feasible start for this right, hence the longest feasible ending here.

## Deque invariant
The deque holds in-window indices in increasing index order and strictly decreasing cost order. Its front is the maximum. When a new index has cost >= a tail candidate, discard that candidate: the new index is at least as large and expires later. Remove the front exactly when it leaves the window. After shrinking, sum and deque both describe the current window. Every singleton has payable cost zero, so the while loop never needs to evaluate an empty deque.

Walkthrough [4,9,2,3], budget 5: [4,9] pays 4; appending 2 pays 6, so remove 4. The window [9,2] pays 2. Append 3 to obtain [9,2,3], paying 5. Answer 3.

## Complexity
Each index is inserted once and removed at most once; both boundaries advance at most n times. Θ(n) time and O(n) worst-case auxiliary space (strictly decreasing costs can fill the deque). Reading every cost is necessary in the worst case. Use long long for sums up to 2e14.

## Common mistakes
- Using the total cost rather than total minus max.
- Storing values without indices, which complicates expiry for duplicates.
- Forgetting to update the running sum when shrinking.
- Using if instead of while; a single deletion need not restore feasibility.
- An old maximum can misstate current feasibility: [100,1,6,6], budget 2, after shrinking past 100, [1,6,6] pays 7, not a value based on 100. Some different problems permit stale maxima when only a length is needed; do not assume that shortcut proves the invariant here.
- Using int for the sum.

## CS61B connections
A deque supports O(1) operations at both ends, unlike erasing from the front of a vector. Dominance pruning and aggregate push/pop counts illustrate amortized analysis. Compare with a priority queue: a heap needs lazy deletion or explicit erase and costs logarithmic time. Contrast yesterday's frequency-based window: the same monotone-boundary proof works, but the maintained statistic is different.
