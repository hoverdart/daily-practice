# Stable Dispatch Manifest — solution notes

## Recognition
A tiny, known integer key range and a stability requirement are the clues. You need a permutation of original indices, not a sorted copy of the priorities. This is a counting-sort problem, not a heap problem.

## Baseline
Selection-style scanning can repeatedly find the next highest unassigned job (O(n²) time, O(n) bookkeeping). More practical: fill an index vector with 0..n-1, then stable-sort by the corresponding priority (typically O(n log n) comparisons, potentially O(n) temporary space; C++ stable_sort can use more comparisons if allocation is unavailable). An ordinary sort with an explicit index tie-breaker is also O(n log n).

## Optimal
1. Count each priority in a fixed 101-entry array.
2. Traverse priorities from 100 to 0. Replace each count by its starting output offset, advancing the running total by the old count.
3. Scan input left to right. Place index i at next[priority[i]], then increment that cursor.

Example [2,5,2,100,5]: counts for 100,5,2 are 1,2,2; their starting offsets are 0,1,3. Scanning left to right yields [3,1,4,0,2].

## Invariant and correctness
Each priority owns a disjoint contiguous block whose length equals its count. Before processing input index i, next[p] points to the first unfilled cell in p's block; the filled cells contain exactly the processed indices of priority p in increasing arrival order. Each insertion preserves that invariant. At the end all blocks are full, descending by priority and stable within a block.

## Complexity
O(n+R) time, O(R) auxiliary space (R=101), O(n) output. For fixed R this is Θ(n) time for nonempty input and constant auxiliary space. Reading and emitting n indices is already Ω(n).

## Common mistakes
- Ascending offsets instead of descending; reversing the final list also reverses equal-priority jobs.
- Losing the old count when replacing it with an offset.
- Returning priorities rather than their original indices.
- Forgetting priority 0 or 100, or using unsigned descending loops that wrap.
- Using std::sort with only priority as comparator and assuming stability.

## CS61B connection
Counting/radix sorting exploits key structure rather than the comparison model. Stability matters in multi-key sorting. The fixed array, prefix-offset construction, and loop invariant are examples of data-structure selection and precise cost modeling.
