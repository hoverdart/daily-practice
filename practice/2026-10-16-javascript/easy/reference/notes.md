# First Nearby Duplicate Signal — reasoning and CS61B connection

## Recognition signals
"Two equal items within k positions" + "earliest second index" points to a **bounded recent-history window**, not a global seen set. A global set incorrectly accepts duplicates that are too far apart. The familiar Set operation is deliberately paired with the previously weak *window boundary invariant*.

## Brute force → optimal
Brute force checks up to k preceding indices for each j: O(n min(n,k)) time and O(1) extra space. You could also remember each ID's most recent index in a Map: O(n) time, O(n) space. The sliding Set reduces extra space to O(min(n,k)) because only recent IDs matter.

**Invariant:** immediately before querying `ids[j]`, the Set contains IDs from exactly indices `max(0,j-k)` through `j-1`, unless the algorithm already returned a match. Those IDs are distinct: if a duplicate had appeared within this maintained window, the algorithm would have returned at its second occurrence. Delete index `j-k-1` when it falls out; then query; then insert current ID.

## Complexity
Each item is inserted once and removed at most once. Average-case Set operations are O(1), giving O(n) expected time and O(min(n,k)) space. When k=0, remove the prior item before querying so no match can occur.

## Common mistakes
- Checking membership **before** evicting the too-old item (off-by-one false positive).
- Using an unbounded global Set.
- Removing the current item rather than `ids[j-k-1]`.
- Assuming k is a number of elements instead of a maximum **index distance**.
- Claiming nested-loop O(n²) for a linear sliding-window implementation.

## CS61B connections
HashSet average O(1) membership; sliding windows/two pointers; invariants over mutable state; time–space tradeoffs versus a last-index HashMap. Test the boundary k=0, k=1, k>=n, and negatives.
