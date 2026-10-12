# Reference Notes — Exactly K Event Types

## Recognition signals
"Contiguous" + "number of distinct values" + "count all subarrays" suggests a frequency-map **sliding window**. The condition "at most K distinct" is monotone when shrinking from the left. "Exactly K" is harder to count directly but equals **atMost(K) − atMost(K−1)**.

## Brute force → optimal
Brute force: for each starting index, extend the end index while maintaining a set; count when the set has size K. This is O(n²) expected time and O(n) space. Enumerating all subarrays explicitly would be even more wasteful.

Optimal: write `at_most(limit)`. Add the new rightmost code to the frequency dictionary. While the dictionary has too many distinct keys, decrement the leftmost code, **delete it if its count reaches zero**, and advance `left`. After shrinking, the valid subarrays ending at `right` start at any index in `[left, right]`, so add `right-left+1`.

The answer is `at_most(k) - at_most(k-1)`. Treat `k=0` as zero because subarrays must be nonempty.

## Invariant and proof
After each inner shrink loop, `[left, right]` has at most `limit` distinct values, and every start before `left` would have too many distinct values (if there were any). Every later start remains valid because removing values cannot increase distinctness. Thus there are exactly `right-left+1` valid endings at `right`.

Each pointer only moves forward, at most n times, so each at-most pass is expected O(n). Two passes are still O(n). The frequency dictionary has at most `min(n, limit+1)` keys transiently (after inserting before shrinking); for K>=1 this is O(min(n,K)). The answer can be O(n²) numerically, but Python integers handle it.

## Common mistakes
- Forgetting `del counts[outgoing]` at zero: `len(counts)` becomes wrong.
- Counting only one window per `right` rather than all valid starts.
- Confusing `k` with window length instead of distinct key count.
- Trying to count "exactly" with a single greedy window and missing multiple valid starts.
- Using `if` instead of `while` when the window needs multiple shrinks.
- Thinking nested loops mean O(n²); `left` never retreats.

## CS61B connection
Hash tables provide expected constant-time frequency updates. The two-pointer scan is an amortized analysis: every element enters and leaves the window at most once. This is deliberate spaced repetition for the October 5 medium log, where the role of the counts dictionary was the main sticking point.
