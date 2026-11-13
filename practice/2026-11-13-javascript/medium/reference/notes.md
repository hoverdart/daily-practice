# Medium reference — Longest Exact Net-Change Run

## Recognition signals

Contiguous interval + exact sum + **negative values** points to prefix sums plus a hash map. Standard nonnegative-sum sliding-window logic is not sound. Example: `[5,-4,3]` has a target-4 full run. Shrinking immediately when a partial sum 5 exceeds 4 discards the eventual solution.

## Brute force → optimal

Try every start and extend each end, maintaining the sum, updating the best for equality. This is **O(n²) time, O(1) auxiliary space**; recomputing every sum is slower.

Let `prefix[k]` be the sum of the first k changes. Interval `[i,j)` has sum `prefix[j]-prefix[i]`, so when current end is j we need `prefix[i] = prefix[j]-target`. The earliest such i produces the longest run ending at j. Keep a `Map` of prefix value to its **first** index; initialize with `0 -> 0`. Query before inserting current prefix to exclude an empty run when target=0. Update the answer for larger length or same length with smaller start.

## Invariant and proof

Before each end j, the map contains the smallest index i<j for every prefix sum seen at earlier indices. Any retrieved i gives a valid nonempty interval with the required sum, and is the *longest* interval with that end because it is the smallest valid start. Every end is examined; choosing the global longest, then earliest start, is correct.

## Complexity

Expected **O(n) time** and **O(n) auxiliary space** for the hash map. The maximum absolute prefix magnitude is at most 140000 × 1000000 = **140,000,000,000**, well under `Number.MAX_SAFE_INTEGER`.

## Common mistakes

Trying sum-based two pointers despite negative values; storing the latest prefix occurrence; overwriting earlier indices; updating the map before querying (empty target-zero intervals); forgetting the initial 0 prefix; incorrect end-inclusive indexing; mishandling ties or missing-match `[-1,-1]`. `Map` avoids coercion of numeric keys in plain objects.

## CS61B connections

Hash-table expected-time reasoning, array prefix invariants, amortized linear scans, and choosing between algorithm families. This is **contrastive review** of sliding-window prerequisites, not just another mechanical window-counting problem.
