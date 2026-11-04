# Medium — Reference reasoning

## Recognition signals

A question about *all contiguous substrings of a fixed length* that satisfy a frequency-based condition signals a **fixed-size sliding window**. The '?' slots mean the required letter counts are **lower bounds**, not exact counts. The unused capacity will fill the wildcard positions automatically.

## Brute force vs optimal

For every starting index, count the length-m substring, compare its 26 letter frequencies against pattern requirements: O((n-m+1)m + 26(n-m+1)) time, O(26) space. It wastes work recounting nearly identical neighboring windows.

Instead, compute a signed **deficit** array. deficit[c] = number of literal c's needed minus number of c's currently in the window. Positive means unmet required copies; negative means surplus. Maintain an integer missing = sum(max(0, deficit[c])).

- Enter c: if deficit[c] > 0, one required copy is now satisfied; decrement missing. Then decrement deficit[c].
- Leave c: increment deficit[c]; if its new value > 0, a required copy was lost; increment missing.
- When length m is established, the signature matches iff missing == 0.

Since the window and pattern have equal length, fulfilling all literal counts leaves exactly enough positions for all '?'. We need not assign wildcards individually.

## Invariant and proof

After adding stream[right] and (when needed) removing stream[right-m], deficit stores pattern literal count minus frequency of each letter in the last min(m,right+1) stream positions. The incremental updates follow algebraically from one entering or leaving character. missing always counts the number of outstanding literal instances, because it changes only when a deficit crosses the positive threshold. Thus missing==0 iff every required literal multiplicity is present.

## Complexity

Pattern preprocessing O(m); each stream character enters once and leaves at most once, O(n). Overall **O(n+m) time** and O(26) extra counting space, excluding up to O(n) output indices. No hash table needed because the alphabet is only 26 symbols.

## Common mistakes / CS61B connections

- Checking only set membership loses multiplicities (two A's are not one A).
- Comparing exact frequency arrays rejects valid wildcard windows.
- Comparing deficit[c]==0 instead of deficit[c]<=0 rejects windows with surplus required letters.
- Updating missing for surplus additions is wrong; use the threshold before decrement.
- On removal, check after increment, since this may create a new unmet copy.
- Off-by-one: remove index right-m when length becomes m+1; report index right-m+1.
- Java HashMap is unnecessary for A–Z: CS61B array indexing and direct-address frequency tables are faster/simpler.
- Contrast with longest-valid-window problems: here the window length is always m, so no while-shrink loop.
