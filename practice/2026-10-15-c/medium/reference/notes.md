# Reference Notes — Longest Bounded Channel Window

## Recognition signals
Longest **contiguous** segment with a constraint that can become invalid when the right endpoint advances suggests a sliding window. Here the constraint is at most k distinct codes. Moving left forward can restore validity; no endpoint ever moves backward.

## Brute force vs optimal
For each left endpoint, try all right endpoints and count distinct codes, taking O(n²) time even with an incrementally updated frequency array. At n=100000 this is too slow.

Optimal: maintain freq[256], left, distinct, and best. On adding events[right], increment distinct only when its frequency changes from zero to one. While distinct exceeds k, remove events[left], advance left, and decrement distinct only when its count becomes zero. After shrinking, the window is valid, so update best with right-left+1.

## Invariant and proof
After each shrink phase, freq[c] is exactly the number of occurrences of code c in the current window, and distinct counts positive frequencies. For each right, left is the earliest valid endpoint not already discarded. Earlier endpoints were invalid and cannot become valid by adding more right-side elements. Therefore the current valid window is the longest valid one ending at right; maximize across right.

## Complexity
Each index is added once and removed at most once: O(n+256) time, O(256) extra space. The nested while is amortized linear.

## Mistakes
- Changing distinct on every occurrence rather than only 0-to-1 and 1-to-0 transitions.
- Updating best before restoring validity.
- Shrinking on distinct >= k rather than > k.
- Using a one-byte frequency counter, which overflows on long runs.
- Failing the k=0 case, where only an empty window is valid.

## CS61B connections
The fixed array is a direct-address frequency table, equivalent to a hash map for a tiny bounded key universe. Compare with minimum covering window (shrink while valid) and exactly-K counting (countAtMost(K) minus countAtMost(K-1)). First identify whether the problem asks for maximum length, minimum length, or number of subarrays.
