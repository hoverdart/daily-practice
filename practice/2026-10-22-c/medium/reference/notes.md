# Reference Notes — Longest Stable Telemetry Window

## Recognition signals
"Longest contiguous interval satisfying a monotone constraint" suggests sliding window. For a fixed right endpoint, removing readings from the left cannot increase max−min. Scalar min/max fail when the outgoing reading was an extreme; a deque of candidate **indices** handles expiration.

## Brute force versus optimal
Scanning each of O(n²) intervals for extrema takes O(n³). Maintaining extrema while extending each fixed left endpoint takes O(n²). A balanced multiset gives O(n log n), but C has no built-in multiset. Two monotonic deques achieve O(n).

## Optimal invariants
Maintain active window [left,right] after adding right:
- maxq stores increasing indices with **strictly decreasing** values; its front is the current maximum.
- minq stores increasing indices with **strictly increasing** values; its front is the minimum.
- Before appending right, pop dominated candidates from the back. The newer index is at least as extreme and outlives them.
- While max−min exceeds limit, advance left and remove deque fronts equal to the old left.
- After shrinking, [left,right] is the longest valid window ending at right. Update best only on strictly greater length; scanning right left-to-right then retains the earliest start on ties.

## Complexity
Each index enters and exits each deque at most once, and left advances at most n times. **O(n)** time, **O(n)** heap space for index arrays. Compute (long long)max - (long long)min: casting **after** int subtraction is too late to prevent signed overflow.

## Common mistakes
- Expiring by value instead of index (duplicates).
- Keeping stale maxima/minima after their indices leave.
- Using int subtraction for INT_MAX - INT_MIN.
- Updating the answer before restoring window validity.
- Replacing the best on ties, selecting a later start.
- Forgetting free() or confusing a linear head/tail deque with a circular buffer.

## CS61B connections
Array-backed deques and representation invariants, amortized analysis, and two-pointer scans. Contrast with Oct 5's frequency-map window: that stores **category counts**; this stores **candidates for extrema**. Also related to sliding-window maximum and monotonic queues.
