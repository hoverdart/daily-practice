# Explanation — Shortest Archive Cut

## Recognition signals
A contiguous deletion is a sliding window, but the condition is on its **complement**, not on the window itself. Growing the deletion never increases outside frequencies. That monotonicity is the key to two pointers.

## Baseline to optimal
Enumerate all O(n^2) intervals and recompute outside counts in O(n) each: O(n^3) time. Incremental counts for each fixed left endpoint improve this to expected O(n^2). A better approach maintains the outside counts while moving both endpoints forward once.

Initialize a Map with the counts over the whole input, and over = number of IDs whose outside count exceeds cap. If over is zero, return 0. As right moves, the new event is removed from the retained archive: decrement its outside count, decrement over only on the transition cap+1 -> cap. While over is zero, record the length and move left forward, restoring that event to the retained archive. Increment over only on cap -> cap+1. Stop shrinking when invalid; expand again.

## Invariant / proof
For deletion [left,right], remaining[x] equals the total occurrences of x outside that interval and over is exactly the number of violated caps. Extending right cannot invalidate a feasible deletion. Moving left rightward cannot repair an invalid deletion, since it restores events. Thus for each right endpoint, shrink until invalid; every shorter interval ending there is invalid. Any discarded left endpoint was already considered in a valid, no-longer interval, and extending it in the future only makes it longer. This proves the global minimum. The initial valid check handles the empty deletion and prevents shrinking an empty valid window.

## Walkthrough
For [1,2,1,3,2], cap=1, outside counts start {1:2,2:2,3:1}, over=2. Remove first 1 -> over=1; remove first 2 -> over=0, length 2. Restore first 1 -> over=1, so stop shrinking. The later windows cannot improve below 2 because two separate IDs each require one removal.

## Complexity
Expected O(n) time with conventional hash-map assumptions: n initial increments, at most n expansions and n shrink steps. O(d) space for d distinct IDs. The input must be inspected in the worst case, giving a linear lower bound. The reference keeps zero-count entries so restoration always has a defined value.

## Common mistakes
- Counting events inside the deletion instead of outside; reverse the update directions if you use inside counts.
- Recomputing all frequencies after each move, or resetting the window on invalidity.
- Updating over on every decrement rather than only a threshold crossing.
- Shrinking with if instead of while; shortest valid windows may require repeated shrinking.
- Forgetting cap=0, empty input, or no deletion needed.
- Using plain object keys instead of a Map with explicit numeric IDs and nullish default.

## CS61B connection
HashMap key/count invariants, amortized analysis of dynamic maps, and the two-pointer extension of array iteration. The same reasoning as a minimum-cover window appears here in a complementary form.

## Transfer
For different caps per ID, replace the single threshold with cap[x]; the same invariant applies. If deleting disjoint blocks is allowed, the single-window monotonic argument no longer solves the new optimization problem.
