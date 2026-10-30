# Explanation — Longest Recalibratable Signal Run

## Recognition signals
"Contiguous interval," "change at most k elements," and "maximize length" suggest a **sliding window**. The number of edits needed is not the number of distinct values: it is `length - frequencyOfMostCommonValue`.

## Brute force versus optimal
**Baseline:** for each left endpoint, extend right and maintain frequencies plus the current exact mode. Scanning all frequencies at each step can be cubic; maintaining the mode while only expanding yields `O(n^2)` time and `O(d)` space.

**Optimal:** one expanding right pointer, one shrinking left pointer, a `Map` of frequencies, and a **nondecreasing historical maximum** `maxFreq`. When `windowLength-maxFreq>k`, discard from the left. Expected `O(n)` time, `O(d)` auxiliary space (up to O(n) distinct values). Each pointer moves forward at most n times.

## Correctness: why the stale maximum is safe
`freq` always describes the **current** window. `maxFreq` is the greatest frequency observed at any time during rightward expansion, so it can overestimate the current mode after shrinking. Thus the test is not a guarantee that every retained window is *currently* transformable.

However, the algorithm seeks only the **maximum length**, not a valid witness interval. Suppose a new record length `L` is achieved. Its permissive test requires `L <= maxFreq+k`. The last time this `maxFreq=f` was established, a real window containing f equal readings existed. In a full-length prefix/suffix expansion around those readings (when at least f+k elements are available), there is a valid window of length f+k; if fewer elements existed, the algorithm cannot exceed that available length. Moreover, with fixed `maxFreq`, the shrinking rule prevents increasing the retained window length beyond its prior maximum; a **new** record requires `maxFreq` to rise. Thus no record length is invented by stale data, and the algorithm never misses a genuinely valid optimum (its relaxation only delays shrinking). If the task required the actual valid interval, track exact mode or verify the candidate.

A simpler intuition: a stale mode can make a current window look valid, but it cannot manufacture a **better answer** than a length previously supported by a real frequency record.

## Common mistakes
- Treating `k` as a limit on distinct values, not replacements.
- Shrinking at `>= k` instead of `> k`.
- Recomputing the mode with `Math.max(...freq.values())` every step (can become quadratic).
- Forgetting to decrement the departing code, or using a global rather than window-local count.
- Returning `maxFreq+k` without capping by available length.
- Assuming a stale `maxFreq` means the **current window** is always valid.

## CS61B connections
Hash-table frequency maps, two-pointer amortized analysis, and loop invariants. The `Map` is a live state table; `maxFreq` is a monotone historical bound. The same distinction appears in lazy data structures and priority-queue algorithms that discard stale entries.
