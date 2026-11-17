# Reference notes — Longest Fair Worker Session

## Recognition signals

The word **contiguous** plus a **per-ID upper frequency cap** suggests a frequency map and two moving boundaries. The additional requirement "at least D distinct IDs" is a **lower** bound, not another violation to shrink away. This is a deliberate trap: the two constraints have opposite monotonic directions.

## Brute force versus optimal

**Brute force:** enumerate all O(n²) intervals, maintaining a fresh or incremental frequency map per left boundary, and check the two constraints. O(n²) expected time with incremental counts, O(n) space; a fully naive recount can be O(n³).

**Optimal:** grow right, increment the incoming ID's frequency. Previously all IDs respected the cap, so only this incoming ID could violate it. While its count exceeds maxPerWorker, decrement workerIds[left], remove zero-count keys, and advance left. The remaining interval is the **longest cap-admissible** interval ending at right. If its distinct-count passes minDistinct, it is also the longest valid interval ending at right; update the global best.

If that maximum-length cap-admissible interval has too few distinct IDs, all shorter suffixes have no more distinct IDs and therefore also fail. Do not shrink just because the lower-bound is unsatisfied.

## Correctness invariant

At the end of cap repair for each right: (1) every frequency matches its exact occurrences in [left,right]; (2) every frequency is at most cap; (3) among suffixes ending at right that satisfy the cap, left is the earliest start. When frequency of workerIds[right] first exceeded cap, any start at or before the removed occurrences was invalid. The shrink loop stops at the earliest now-legal start. Thus the algorithm examines the best possible candidate for every right and cannot miss the global optimum. Equal-length ties retain the earlier left.

Each element enters exactly once and leaves at most once. Expected total O(n) time (average O(1) hash operations) and O(min(n, unique IDs)) auxiliary space.

## Java syntax

~~~java
Map<Integer, Integer> freq = new HashMap<>();
freq.put(id, freq.getOrDefault(id, 0) + 1);
int remaining = freq.get(oldId) - 1;
if (remaining == 0) freq.remove(oldId);
else freq.put(oldId, remaining);
int distinct = freq.size();
~~~

## Common mistakes

- Shrinking the window on distinct < minDistinct; shrinking cannot add distinct IDs.
- Counting total repeated values instead of the maximum frequency of any one worker.
- Leaving zero-frequency keys in the map, inflating the distinct count.
- Checking only whether the incoming ID has ever appeared before instead of its current-window frequency.
- Returning a single maximum length instead of the requested inclusive indices.
- Mishandling nonempty-session semantics for empty input and minDistinct=0.
- Updating on equality without checking earliest-left tie-breaking.

## CS61B connections

Hash tables, expected versus worst-case lookup, loop invariants, aggregate two-pointer complexity, and the distinction between a monotone constraint and a lower-bound acceptance check. This revisits the October 5 frequency-map difficulty while demanding a different recognition cue from the November 10 simultaneous-upper-bound window.

