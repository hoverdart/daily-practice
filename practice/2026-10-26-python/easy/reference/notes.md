# First Sufficient Cache Slot — Reference Notes

## Recognition signals
A **sorted** array, repeated queries, and wording like "first index satisfying a threshold" indicate **lower-bound binary search**. Duplicates mean ordinary "find any equal element" search is insufficient.

## Brute force → optimal
A linear scan per request takes O(nq) time and O(q) output space. Because capacities are sorted, the predicate `capacities[i] >= required` switches at most once from false to true. Binary search for that boundary separately for each request.

## Invariant and example
For each request, maintain the half-open candidate interval `[lo, hi)`: all indices **strictly below** `lo` are known too small; any possible first sufficient slot lies inside the interval, or equals the sentinel `n` if none exists. When `capacities[mid] < required`, discard through `mid` with `lo = mid+1`; otherwise keep `mid` with `hi = mid`.

Trace `[1,2,2,5]`, request 2: start `[0,4)`; mid 2 meets threshold → `[0,2)`; mid 1 meets → `[0,1)`; mid 0 fails → `[1,1)`. Answer 1, not 2.

## Complexity
With n slots and q requests: O(q log(n+1)) time, O(q) output space, O(1) auxiliary search space. For n=0, every answer is -1. Python integer arithmetic does not overflow.

## Common mistakes
- Returning any matching duplicate instead of the **first**.
- Updating `lo = mid` when mid is too small: infinite loop for two candidates.
- Using `hi = mid-1` while also treating `hi` as exclusive.
- Forgetting that `lo == n` means no valid slot.
- Sorting capacities inside the function, which would change original indices and violate the contract.

## CS61B connections / Python recall
This is the same ordered-search invariant behind binary search trees' ceiling/lower-bound operations and the logarithmic cost-model analysis. `bisect.bisect_left` is the standard-library equivalent, but manual implementation tests your reasoning. Unlike hashing, ordered search can answer inequality queries. Review `[lo,hi)` boundaries before interviews.
