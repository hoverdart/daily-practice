# Reference notes — Shortest Incident Evidence Segment

## Recognition signals

"Shortest **contiguous** part satisfying **at least** these item counts" strongly suggests **expand-right, shrink-left sliding window**, backed by a frequency map. Required duplicates mean a multiset, not just a Set. A reset barrier means clearing per-segment state, not concatenating across segments.

## Baseline versus optimal

- **Brute force:** enumerate O(n²) candidate segments and count/check requirements from scratch, costing up to O(n³) in a direct implementation; incrementally counting each start can bring this closer to O(n² + n·r), where r is number of distinct requirements.
- **Optimal:** build `need` frequencies in O(m) for m=required.length. Maintain `have` counts and `missing` = total *individual required occurrences* still unavailable. On right expansion, decrement `missing` only if this new copy is useful. At `missing===0`, update answer and shrink left until one required copy is lost. At a barrier, clear the counts, reset missing, and start the next segment.

## Proof / core invariant

For every active non-barrier interval `[left,right]`, `have[x]` counts the copies of required code x inside the interval, and `missing = Σ max(0, need[x]-have[x])`. Validity is equivalent to missing zero. For each right endpoint, repeatedly shrinking a valid window finds the shortest valid left endpoint for that right; any further shrink makes it invalid. Comparing these candidates obtains the global shortest, and updating only for *strictly* shorter lengths preserves earliest-start ties.

## Complexity

- Expected **O(n+m)** time with standard expected O(1) Map operations and **O(r)** extra counter memory, where r is distinct required codes (also O(n+m) for the output-independent input sizes).
- At most n expansions, n shrinks. A `Map.clear()` at each barrier clears only keys used *since the prior barrier*, so all reset-cleared entries over disjoint segments sum to O(n) even under an implementation that charges per entry.
- Hash maps have adversarial caveats; expected time is the standard interview assumption.

## Common mistakes

- Using a Set and accepting only one copy of a required repeated code.
- Decrementing missing for copies **above** the required quantity.
- Shrinking after the window has become invalid, skipping viable candidates.
- Forgetting to reset both left and missing after `"#"`.
- Off-by-one: return `[left,right+1]`, not inclusive right.
- Accidentally mutating `codes` or using truthiness for a valid count of zero.

## CS61B connections

Hash table frequencies and the linearity of an array-based two-pointer scan; compare with queues/deques for extrema-based windows. Unlike a signed-sum window (which may need prefix sums), multiplicity satisfaction behaves predictably as the window expands, making shrinking safe.

