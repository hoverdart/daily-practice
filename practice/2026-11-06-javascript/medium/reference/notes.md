# Exactly K Signal Collision Pairs — Reasoning and Reference Notes

## Recognition signals

"Count contiguous intervals", "exactly k", and a quantity that **cannot decrease when the right boundary grows** suggest counting via two sliding windows (at most k minus at most k-1). A Map of frequencies captures duplicate multiplicities. This is not merely counting distinct values.

## Brute force vs optimal

**Baseline:** Enumerate all O(n²) starting and ending positions. Extend each interval incrementally: when x is added, add its current count to the pair total. Check whether the pair total equals k. O(n²) time, O(u) auxiliary frequency space (or O(n³) if recalculating each interval).

**Optimal:** Implement F(limit) = number of nonempty windows with at most limit collision pairs. Return F(k)-F(k-1). Maintain left, a Map of counts, and pairs in current inclusive window [left,right]. Each newly appended x contributes old freq[x] pairs. If pairs exceeds limit, remove ids[left] (a y occurring f times before removal destroys f-1 pairs) and advance left. Once valid, all right-left+1 suffix windows ending at right are valid, so add that number.

## Correctness invariant

After the while loop, [left,right] has <= limit collision pairs. No left boundary smaller than left is legal: such a larger window still has too many pairs, because adding positions cannot *decrease* pair count. Every boundary from left through right is legal because removing prefix positions cannot increase pair count. Thus the count of qualifying windows ending at right is right-left+1. Summing over right counts each interval exactly once. Subtracting at-most counts retains precisely those with k pairs.

If limit < 0, F(limit) = 0 (even an empty window is not counted). On k=0, this makes the formula work.

## Complexity

Each right endpoint enters once and each left endpoint leaves at most once for each atMost call. Average/expected hash-map operation O(1), so **expected O(n) time**, O(u) auxiliary space per pass, plus O(1) counters. In adversarial hash collision environments hash-map operations can degrade, but JavaScript Map is the appropriate interview default.

At n=120,000, maximum count of intervals is n(n+1)/2 = 7,200,060,000; maximum pairs in one interval is n(n-1)/2 = 7,199,940,000. Both are well below Number.MAX_SAFE_INTEGER (9,007,199,254,740,991).

## Common mistakes

- Increasing pairs by 1 instead of by existing frequency when appending x.
- Removing y and subtracting its old count instead of old count - 1.
- Counting "distinct duplicate IDs" instead of unordered pairs of equal positions.
- Forgetting F(-1)=0 when k=0.
- Returning only the length of the longest valid window rather than the number of windows.
- Using a Set, which loses multiplicity; deleting Map entries too early or keeping invalid negative counts.
- Missing windows that start later than the minimal valid left.
- Accidentally interpreting noncontiguous subsequences as windows.

## CS61B connections

Hash tables support O(1) expected frequency maintenance. The two-pointer argument is an amortized analysis: despite nested loops, each index is processed a constant number of times. This revisits the exact frequency-map bookkeeping the previous completed sliding-window attempt found difficult, but with a new pair-count invariant and a counting objective.
