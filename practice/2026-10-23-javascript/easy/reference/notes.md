# Explanation — Insert a Maintenance Window

## Recognition signals
"Sorted intervals", "insert one interval", and "merge overlapping ranges" suggest **one left-to-right pass**. The sorted/disjoint precondition eliminates the need to sort. Think of the merge step of merge sort: the cursor never moves backward.

## Brute force versus optimal
**Brute force / generic baseline:** append the new interval, sort all n+1 intervals by start, then merge neighbors. Sorting dominates at **O(n log n)** time; output takes O(n) space.

**Optimal:** scan the three regions. First copy intervals with end < start; they cannot overlap. Next absorb every interval whose start <= the current merged end, updating both boundaries. Finally append the merged interval and copy everything remaining. **O(n)** time, **O(n)** required output space, **O(1)** auxiliary space excluding output.

## Correctness invariant
Before each scan step, all copied intervals are finalized and cannot overlap the growing merged request. During the middle loop, [start,end] equals the union of the inserted interval and all overlapping intervals already consumed. Because existing intervals are sorted and mutually disjoint, after the first interval starting > end, none of the later intervals can overlap the merged request.

## Common mistakes
- Using <= rather than < in the "strictly before" test: touching **closed** endpoints must merge.
- Checking overlap only against the *original* added end, rather than the **expanded** end.
- Mutating input pairs or returning the original inner arrays.
- Sorting the input even though it is already sorted.
- Forgetting empty input, negative endpoints, or [x,x] singleton intervals.

## CS61B connections
This is the **merge** idea from sorting and an example of an O(n) two-pointer/cursor invariant. Each interval is consumed at most once, just as each element is advanced once during merge sort's linear merge step. No hash map or heap is needed.

