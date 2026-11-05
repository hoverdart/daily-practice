# Calm Intervals — Recognition and Optimal Reasoning

## Recognition signals

A subarray is valid when a constraint involving its maximum and minimum is met. Adding more elements cannot reduce max-min, and removing elements cannot increase max-min. This monotonicity in window inclusion points to **two pointers + sliding window**. Computing max/min naively for every window would be far too slow.

Two monotonic deques are useful whenever a moving window needs its maximum and minimum with amortized O(1) updates.

## Baseline versus optimal

**Brute force:** For each start, extend the end and maintain the running min and max. Every interval is considered once, giving O(n^2) time and O(1) auxiliary space. If you recompute min/max from scratch each time, the cost becomes O(n^3).

**Optimal:** Keep indices of potential maxima in a decreasing deque and potential minima in an increasing deque. For every right endpoint:
1. Pop dominated indices from the back of both deques.
2. Append right to both.
3. While max-min exceeds tolerance, remove the outgoing left index from deque fronts when present, and increment left.
4. Add right-left+1 to the answer.

The deques store **indices**, not values, so we know whether their front fell outside the window. A value dominated by an equal or newer value need not be retained because the newer one remains available at least as long as the old one.

## Invariants and count proof

At the end of shrinking, [left,right] is valid and no earlier left boundary would be valid. The front of maxq gives the window maximum; the front of minq gives the minimum. Every suffix [i,right] with i >= left is also valid because deleting a prefix cannot enlarge the range. Every earlier-starting interval is invalid by the minimum-left invariant. Therefore exactly right-left+1 new intervals end at right.

Each index is appended once and popped at most once from each deque, so even though loops are nested in the code, total deque work is O(n). The left boundary also moves forward at most n steps.

## Complexity and integer safety

Time O(n); extra space O(n) for two arrays of indices. The number of windows can be n(n+1)/2: with n=200,000, that is 20,000,100,000, requiring 64-bit. INT_MAX minus INT_MIN is 4,294,967,295, which overflows 32-bit signed int; convert operands to int64_t *before* subtracting.

## Common mistakes

- Counting only the longest or shortest valid window rather than all valid intervals.
- Treating the deque contents as all window indices instead of candidates for extrema.
- Forgetting to evict expired indices as left advances.
- Using < instead of <= or vice versa without considering equal values and indices; either tie policy can work if handled consistently.
- Widening the answer but not max-min subtraction.
- Assuming the while-loop is O(n) per right; amortized analysis bounds it globally.
- Failing n=0 or tolerance=0 cases.

## CS61B connections

This is a CS61B deque/circular-array application: front and back operations let us maintain a compact summary of an interval. It also illustrates amortized reasoning akin to resizing arrays and monotonic stack exercises. The proof is about **invariants**, not merely recognizing a template.

