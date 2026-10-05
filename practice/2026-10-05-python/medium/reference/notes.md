# Notes — Stable Sensor Window

## Recognition signal
A **longest contiguous interval** with a condition repairable by moving the left boundary suggests sliding window.

## Brute force
Enumerate every subarray and count distinct values: O(n²) or worse.

## Optimal approach
Maintain `left`, expand `right`, and keep a frequency map. If there are more than k distinct codes, advance `left` until valid.

Time: O(n), since each element enters once and leaves at most once. Space: O(k), with k+1 keys transiently.

## Invariant
After shrinking, `readings[left:right+1]` has at most k distinct values.

## Common mistakes
- Using `if` instead of `while` to shrink.
- Forgetting to delete zero-count keys.
- Confusing subsequences with contiguous subarrays.
- Rebuilding a set for every window.

## CS61B connection
The frequency map is hashing. The runtime uses amortized reasoning: despite a nested loop, each boundary advances only O(n) times.

## New pattern
Sliding window works when a contiguous range can expand incrementally and a violated local constraint can be repaired by advancing the left edge.
