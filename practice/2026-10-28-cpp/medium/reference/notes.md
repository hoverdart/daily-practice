# Reference notes — Count Overloaded Signal Windows

## Recognition signals
The task asks for the number of **contiguous subarrays** satisfying a threshold on a statistic that only increases when elements are appended and only decreases when elements are removed. This is a monotone sliding-window signal. Equal-ID **pairs**, not just duplicate IDs, determine validity. This is a spaced repetition of the October 21 frequency/pair invariant, now counting windows rather than maximizing length.

## Brute force versus optimal
A literal brute-force algorithm enumerates O(n²) intervals and counts O(n²) index pairs within each: O(n⁴). Maintaining counts separately for each fixed left boundary can reduce this to O(n²) expected time. The optimal solution counts all windows minus windows containing **at most k-1** equal-ID pairs. The latter is directly compatible with the standard at-most sliding-window template.

## Invariant and counting proof
Maintain `freq[x]` equal to the number of occurrences of x in the current inclusive interval `[left,right]`. Maintain `pairs = sum_x freq[x]*(freq[x]-1)/2`. Appending x with old frequency f creates exactly f new equal-ID pairs, so add f. Removing x with old frequency f destroys f-1 pairs, so subtract f-1, then decrement/erase its count. Shrink while `pairs > k-1`.

After shrinking, `[left,right]` is valid, and **every suffix** `[s,right]` for `left<=s<=right` is also valid because removing elements cannot create pairs. Any earlier start is invalid (the loop stopped at the first valid start). Thus exactly `right-left+1` at-most windows end at right. Sum over right and subtract from `n(n+1)/2`.

For k=0, every nonempty window qualifies; returning total avoids an invalid negative at-most budget. If k exceeds the maximum possible number of pairs, the algorithm naturally returns zero.

## Complexity
Every element enters once and leaves at most once, so there are O(n) hash operations: **expected O(n)** time, O(d) auxiliary space for d distinct IDs in the current window (worst-case O(n)). Hash-table adversarial collisions can worsen worst-case time. Pair counts and window counts can approach 20 billion at n=200000, so use 64-bit `long long`.

## Common mistakes
- Add only one pair for each repeated ID instead of its old frequency.
- Subtract f instead of f-1 on removal.
- Forget to erase keys with zero count (wastes memory and breaks `freq.size()` interpretations).
- Count `right-left` rather than `right-left+1`.
- Treat k=0 as if the at-most budget were a normal nonnegative threshold.
- Use `int` for total, pair count, or answer.
- Assume nested `while` means quadratic; each left movement is charged once.

## CS61B connections
This uses hash-table average O(1) updates, load-factor intuition, and amortized two-pointer analysis. The mathematical pair-count invariant is analogous to maintaining aggregate metadata in a data structure after each update. Compare with the October 21 longest-valid-window task: same maintained statistic, different global aggregation.

