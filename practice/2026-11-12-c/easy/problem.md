# Easy — Two-Log Replay Quota

Two data centers each have a **sorted** log of event IDs (signed integers). A replay check pairs an occurrence from the left log with an occurrence bearing the same ID from the right log. Each occurrence may be used once. Because one ID can dominate a log, policy permits at most **quota** paired occurrences of any one distinct ID.

Return the maximum total number of replay pairs across all IDs.

Implement in solution.c:

~~~c
#include <stddef.h>
size_t count_capped_matches(const int *a, size_t na,
                            const int *b, size_t nb,
                            size_t quota);
~~~

The input arrays are sorted nondecreasingly and must not be modified. NULL is permitted for a zero-length array. A zero quota always produces zero.

## Examples

- a = [-2,-2,3,3,3,8], b = [-2,-2,-2,3,3,7], quota = 2 -> **4** (two -2 pairs and two 3 pairs).
- a = [1,1,1], b = [1,1], quota = 1 -> **1**.
- a = [5,6], b = [1,2], quota = 5 -> **0**.
- Empty log or quota = 0 -> **0**.

## Constraints

- 0 <= na, nb <= 200,000.
- IDs may be INT_MIN or INT_MAX.
- 0 <= quota <= SIZE_MAX.
- Required: **O(na+nb) time, O(1) extra space**.

## Questions to answer

1. What happens when a[i] < b[j]? Why can the unmatched element be permanently skipped?
2. When the IDs match, why should you process entire *runs* at once?
3. How does min(countA, countB, quota) arise?
4. Why does subtraction-based integer comparison risk overflow for extreme IDs?

