# Merge Service Windows — Recognition and Solution Notes

## Recognition signals

Words like **merge**, **overlapping time ranges**, **continuous coverage**, and **touching endpoints** usually point to sorting by start then scanning. Unlike a shortest-path graph problem, all relevant future interactions can be determined from the sorted order.

## Brute force vs optimal

**Brute force:** Connect reports i and j if their closed intervals overlap or touch, then find connected components with DFS/union-find and replace each component by its min start and max end. Examining every pair uses O(n^2) overlap checks; the resulting graph can contain O(n^2) edges. This is useful as a tiny-input independent oracle, not at n = 200,000.

**Optimal:** Sort pairs by (start, end). Initialize output with a **copy** of the first pair. For each next [s,e]:

1. If s <= output[-1][1], merge it by setting output[-1][1] = max(output[-1][1], e).
2. Otherwise append a **new** [s,e] pair.

The inequality is <= because the intervals are closed and touching endpoints count.

## Loop invariant and correctness

After consuming the first k sorted reports, the output is exactly the minimal list of non-touching merged components for those k reports, ordered by start. Its last interval is the only current component a future report might extend.

For the next interval [s,e]: if s <= last.end, it overlaps or touches the last component; their union is [last.start, max(last.end,e)], so extending is correct. If s > last.end, it cannot overlap an earlier component either: earlier merged components end **before** the last component begins. Further reports have starts >= s, so no later report can bridge the strict gap. Appending is therefore final for earlier components. This proves the invariant inductively.

## Complexity

Python sorted takes O(n log n) worst-case comparisons; the sweep is O(n). The sorted list and output both need O(n) extra space, so overall O(n) auxiliary space including output. For n=0 return [] without indexing.

## Common mistakes

- Using s < last.end; this incorrectly leaves touching windows separate.
- Replacing last.end by e rather than max(last.end,e); nested reports can shorten the merged interval.
- Sorting or mutating the input in place, violating the non-mutation requirement.
- Only comparing adjacent original windows without tracking the accumulated merged end; overlaps can be transitive.
- Assuming all intervals are positive; negative timestamps are legal.
- Accidentally sharing original inner lists; output should contain new lists.

## CS61B connections

**Sorting** is the dominant cost; comparison-sorting runtime is O(n log n). The scan is an invariant-based greedy algorithm and an implicit connected-components computation on an interval-overlap graph. Thinking of the brute-force graph explains correctness, while the sorted sweep avoids constructing its quadratic edge set.
