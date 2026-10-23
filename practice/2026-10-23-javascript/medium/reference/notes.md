# Explanation — Shortest Required-Signal Window

## Recognition signals
"Shortest **contiguous** interval containing all required items" points to **expand right, then shrink left while valid**. The requirements are a *multiset*, so a Set cannot represent how many copies are still needed. Use a Map.

## Brute force versus optimal
A naive method enumerates O(n²) windows and scans the window or recounts requirements for each: O(n³ + n²r) in the most direct implementation. Even with prefix-frequency preprocessing, enumerating every window costs at least O(n²).

The optimal method builds a Map in O(r), then advances right exactly n times and left at most n times. With expected O(1) Map operations, **O(n+r) expected time**, **O(u) auxiliary space** for u distinct required IDs. Input is not copied.

## Two exact invariants
- need.get(x) = requiredCount(x) - countOfXInCurrentWindow. A **positive** value is a deficit, zero is satisfied, and a **negative** value means extra copies are present.
- missing = sum over required IDs of max(need.get(x),0). Thus missing === 0 iff the current window covers the required multiset.

On adding x, decrement missing **only if** its previous deficit was positive. On removing x, increment missing **only if** its updated deficit becomes positive.

For each right endpoint, once valid, repeatedly record the current candidate and advance left until the window becomes invalid. Every shorter valid window ending at right has been examined. Strict length comparison preserves the earliest start on ties because candidate starts are encountered in increasing order.

## Common mistakes
- Counting only distinct required IDs instead of required **occurrences**.
- Treating extras as missing when need[x] goes negative.
- Shrinking while **invalid** (the usual longest-valid pattern) instead of while **valid**.
- Updating best after removing the element that made the window invalid.
- Forgetting empty required → [0,-1] and impossible → [-1,-1].
- Using a plain object with stringified keys rather than a Map for signed integer IDs.
- Claiming O(n²) because of the nested while: each pointer moves forward at most n times.

## CS61B connections
HashMap/Map frequency counts and their expected constant-time operations come from CS61B hashing. The O(n) bound is an **amortized** argument analogous to deque and dynamic-array analyses: a left endpoint is removed only once. This problem is a deliberate contrast to the "longest valid" windows in earlier sets.

