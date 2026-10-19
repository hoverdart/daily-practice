# Zero-Balance Telemetry Spans — Reference Notes

## Recognition signals
"Count **contiguous** segments whose sum equals a target" + negative numbers + large n strongly suggests **prefix sums and a hash frequency map**. A sliding window that shrinks when the sum is too large is unsafe with negative values because sums are not monotone.

## Brute force → optimal
Brute force: fix every left endpoint, extend the right endpoint while maintaining a running sum; O(n²) time and O(1) extra space. Do not recompute every slice sum (that would be O(n³)).

Define P[j] = sum(values[0:j]). The segment values[i:j] sums to zero iff P[i] = P[j]. For each new prefix P[j], **every previous occurrence** of that prefix is a distinct valid starting boundary. Count those occurrences in a dictionary. Initial P[0]=0 exists even before reading a value.

## Invariant / short trace
Immediately before processing the next value, seen[s] is the number of **previous prefix boundaries** having sum s; answer counts all zero-sum spans ending before the new boundary.

For [2,-2,3,-3], prefix boundaries are 0,2,0,3,0. Frequencies of 0 encountered before each new matching 0 are 1 and then 2, yielding 1+2=3 spans.

Order matters: **add seen.get(prefix,0) to answer before incrementing seen[prefix]**. Otherwise you incorrectly count an empty segment ending at the current boundary.

## Complexity
Expected O(n) time and O(n) auxiliary space; worst-case hash-table behavior depends on hashing, as usual. Python integers grow as needed, so the answer can be larger than 2³¹-1.

## Common mistakes
- Forgetting seen={0:1} loses spans starting at index 0.
- Incrementing the current prefix frequency before counting creates an extra empty span.
- Using a set instead of a frequency dictionary undercounts repeated prefix sums.
- Trying positive-only sliding-window logic with negative changes.
- Mistaking subsequences for contiguous subarrays.

## CS61B connections / Python recall
HashMap/HashSet distinction: **multiplicity matters** here. This is the prefix-sum analogue of storing prior states for constant-expected-time lookup. Python: counts.get(key,0) is a read with default; counts[key] = ... updates; dict membership tests keys. Compare with the October 5 easy set-lookup success, now upgraded from existence to counts.

