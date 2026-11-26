# Reasoning

**Recognition:** sorted data + many inclusive range queries suggests boundary search, not scanning or hashing. Duplicates make searching for any matching index insufficient.

**Baseline:** scan all n readings per query, O(nq) time and O(1) auxiliary space. Better: find first index >= lo and first index > hi. Every qualifying index lies in the half-open interval between them; subtract. For reversed bounds return zero first.

**Invariant:** in each binary search, all indices before l fail the target predicate and all indices at or after r satisfy it (within the array). The first satisfying index is in [l,r]. At l=r it is located, or n if none. Midpoint updates preserve the invariant and strictly reduce r-l. Example: [2,2,8], [2,2] -> boundaries 0 and 2.

**Complexity:** O(q(1+log(n+1))) time; O(1) extra space excluding caller output. Each search halves a range of n+1 possible boundary positions. No allocation or mutation.

**Common mistakes:** use `hi+1` (INT_MAX overflow), return any equal index, use r=n-1 and lose the n sentinel, forget reversed bounds or empty array, confuse inclusive value bounds with half-open index bounds. Use `l+(r-l)/2`. C arrays do not carry lengths.

**CS61B:** binary search and logarithmic runtime; arrays/random access, duplicate-key semantics, loop invariants. Contrast with a balanced BST augmented with subtree sizes for dynamic range counts.
