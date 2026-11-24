# Longest Quiet Block — Solution notes

## Recognition signals
Contiguous block, longest valid length, and a budget on a statistic that never decreases when extending right are strong sliding-window signals. The key is to update the statistic incrementally rather than recount every pair.

## Baseline
Enumerate each left boundary, then extend right. Comparing the incoming ID against all previous positions in that block costs O(n³) total (the test oracle deliberately does this). Keeping a fresh frequency map per left reduces it to expected O(n²) time, O(n) space. Reuse the same map instead.

## Derive the statistic
A frequency f contributes f(f-1)/2 unordered equal pairs. Adding a copy changes f to f+1, adding f pairs. Removing a copy from frequency f changes it to f-1, removing f-1 pairs. No other ID's contribution changes.

Maintain freq for [left,right] and a long pairs equal to the sum of all such contributions. Extend right; while pairs > budget, remove ids[left] and advance left. Record right-left+1 after shrinking.

## Correctness
Adding positions never removes pairs; removing positions never adds pairs. Once a start index has been discarded because its window was over budget, extending that same window cannot make it valid. For each right, shrink stops at the earliest feasible start, which yields the longest valid window ending there. Maximizing over right endpoints is globally optimal.

Example [1,2,1,2,1], budget 2: pair totals after the first four arrivals are 0,0,1,2. The fifth adds two new pairs, reaching 4. Removing the first 1 removes two pairs and leaves a valid length-4 window.

## Complexity
Each boundary advances at most n times. Expected O(n) time with ordinary HashMap operations and O(d) auxiliary space, where d is the maximum distinct IDs held in the window (at most n). Java hash-table collision behavior and resizing matter; do not claim unconditional worst-case O(1) lookup. A length-200000 all-equal window contains 200000*199999/2 = 19,999,900,000 pairs, requiring long.

## Common mistakes
- Adding 1 rather than the old frequency counts repeated arrivals, not pairs.
- Subtracting the old frequency rather than old frequency minus one removes one pair too many.
- Resetting the entire window on a violation discards useful suffixes.
- Updating the best length before shrinking counts invalid windows.
- Leaving stale zero-frequency keys may waste memory; remove them.
- Budget zero is valid; every singleton has zero pairs.

## CS61B connections
HashMap as an abstraction over hashing/buckets/load factor, array indexing, and aggregate runtime reasoning. The invariant is analogous to maintaining size in a linked or array-backed list: update exactly the state that changes. Compare with yesterday's exactly-K problem: the target here is a monotone inequality, not an exact distinct count.
