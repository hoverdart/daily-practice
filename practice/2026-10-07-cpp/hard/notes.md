# Notes — Stable Signal Under Noise

## Recognition signals
Longest contiguous window plus constraints repairable by removing from the left => sliding window. Distinct count needs a frequency map. Repeated moving-window min/max suggests monotonic deques.

## Brute force -> optimal
Brute force can reach O(n^3). Sliding window plus multiset is O(n log n). Two monotonic deques maintain min/max in amortized O(1), yielding expected O(n).

## Core invariants
`freq` represents the current window. `minQ` keeps candidate indices in nondecreasing value order; `maxQ` in nonincreasing order. After shrinking, both constraints hold.

## Complexity
Expected O(n) time: every index enters and leaves each deque at most once. O(n) worst-case space.

## Common mistakes
Store indices so expiration is easy. Erase hash keys only at zero count. Cast max-min to `long long` to avoid overflow.

## CS61B connection
Synthesizes hashing, deques, amortized reasoning, and sliding window. It revisits the recent low-confidence window pattern while adding one new invariant.
