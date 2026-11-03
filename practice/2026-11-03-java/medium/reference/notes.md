# Reference Notes — Longest Window With Limited Handoff Types

## Recognition signals
"Longest contiguous segment", "at most K distinct", and deletions from the **left** while appending on the **right** signal a variable-size sliding window with a hash-based frequency map. Here the tracked objects are not array entries: they are **directed edges between adjacent entries**. This is the twist that determines correct updates.

## Brute force versus optimal
For every left endpoint, extend the right endpoint while adding unique directed transitions to a set; check valid windows. This takes expected O(n²) time and O(n) auxiliary memory. Optimally, maintain a `HashMap<Long,Integer>` counting occurrences of each directed transition whose **both endpoints** lie inside the current window. A new right item introduces at most one edge; removing the left item removes at most one edge. Shrink until there are no more than K distinct handoff types.

## Core invariant and proof
Immediately before recording a candidate, `frequency` has exactly the counts of all *unequal adjacent ordered pairs* from indices `left..right`. This holds initially for an empty window. Extending `right` introduces only `(right-1,right)`; shifting `left` removes only `(left,left+1)`. Each update retains the invariant. As moving `left` cannot introduce new handoff types, the while loop restores validity. For fixed `right`, the resulting left boundary is the **smallest left** whose window is valid; any earlier left has too many distinct handoffs. Therefore we consider the longest valid window ending at every right endpoint. Updating only on a *strict* length improvement preserves the earliest-left tie break.

## Complexity
Every right index is visited once; left increases at most n times total. Each hash-map operation is expected O(1), giving **expected O(n) time**, O(n) worst-case auxiliary space for the frequency map. Distinct directed transitions can be Θ(n).

## Common mistakes
- Counting unique device IDs rather than unique directed handoff pairs.
- Counting unchanged adjacency `(x,x)`, which is explicitly excluded.
- Treating `(a,b)` and `(b,a)` as equal.
- Forgetting to delete a key at zero frequency: `map.size()` then lies.
- Removing the *wrong* edge when shifting the left boundary; the dropped edge is `types[left]→types[left+1]`.
- Removing the old left edge **before adding** the new right edge is possible, but be precise about which window each update describes.
- Concatenating int IDs into strings when a lossless 64-bit packing works. Shift a signed `from` to the high 32 bits and mask `to` to the low 32: no collisions even for negative values.
- Wrong tie-breaking or returning `right` inclusive instead of exclusive.

## CS61B connections
HashMap occupancy and frequency invariants, arrays/adjacency intuition (handoffs are edges of a path graph), and amortized cost models for two-pointer scans. Compare with ordinary "at most K distinct values": the structural difference is *what* the map tracks and *when* those entities enter/leave the window.

## Follow-up
How would the implementation change if handoffs were **undirected**, meaning `2→3` and `3→2` were the same type?