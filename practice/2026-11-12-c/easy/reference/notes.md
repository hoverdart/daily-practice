# Easy — Recognition, reasoning, and CS61B transfer

## Recognition signals

Two *already sorted* collections, matching keys, duplicates with multiplicity, and an objective asking how many elements can be paired. This suggests the merge-step pattern / two pointers. You do not need a hash table or nested scans.

## Brute force to optimal

Brute force could scan the entire right log for every **distinct** left ID to count matches, taking O(na*nb) worst-case time, O(1) additional space (or sort a copied unsorted input first, but the arrays here are already sorted). A hash-based counting approach uses O(na+nb) expected time but O(distinct IDs) space.

**Optimal:** i and j point to the first unprocessed left/right elements. If a[i] is smaller, it cannot match any later right value, so move i; similarly for b[j]. When values agree, count whole equal-ID runs on both sides. They contribute min(runA,runB,quota) independent of other IDs.

## Invariant and complexity

At the top of the loop, all IDs/occurrences strictly before indices i and j have already been resolved; no remaining pair needs them. Both indices only advance. Each array position is processed a constant number of times: **O(na+nb) time, O(1) space**. Result cannot exceed min(na,nb), so size_t is sufficient.

## Common mistakes

- Count one match and advance both only once, forgetting quotas and runs.
- Permit the same occurrence to be used multiple times.
- Use (a[i]-b[j]) as a comparator; signed int overflow is undefined.
- Assume the quota fits in int; use size_t as specified.
- Dereference a NULL pointer for a zero-length input.
- Accidentally count all duplicate occurrences rather than capping per distinct ID.

## CS61B connections

This is the same monotone-progress reasoning used by **merge sort's merge**, sorted-list intersection, and two-pointer interval scans. Explicitly state the pointer invariant; do not use an O(nm) nested loop when ordering rules out candidates.

