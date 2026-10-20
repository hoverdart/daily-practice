# Reference — Longest Stream with Limited Repeated Types

## Recognition signals
“Longest **contiguous** segment satisfying an upper bound on a quantity” plus “removing elements cannot make it worse” strongly suggests a **variable-length sliding window**. The unusual detail is that the constraint counts **types with frequency >= 2**, not duplicates or total distinct types. This forces careful bookkeeping.

## Brute force → optimal
Enumerate all O(n²) windows, update a frequency map as each right endpoint advances, and count the types whose frequency is >=2. That is O(n²) expected time with incremental counts (or O(n³) if rebuilding counts). Instead, keep one window `[left,right]` and a map `count`. Expand right once per iteration. If the number of repeated types exceeds `k`, increment left until valid again.

## Core invariant
After the inner while loop, `count` stores exactly the frequencies of `events[left..right]`, and `repeatedTypes` equals the number of keys with count >= 2. On insertion, only **1→2** increases repeatedTypes. On removal, only **2→1** decreases it. Other changes do not cross the threshold. Delete a key when its count becomes zero to keep the map accurate and bounded by the active window.

The validity predicate is **downward closed** under removing elements: removing an occurrence can never increase the number of repeated types. Therefore, once we shrink to validity, `[left,right]` is the **longest valid window ending at right**: every earlier left boundary would be invalid, and every later boundary gives a shorter window. Checking that candidate for each right endpoint finds a global optimum. Prefer a smaller left index on ties.

## Complexity
Each index is inserted once as `right` advances and removed at most once as `left` advances. Total **O(n) expected time** with average O(1) HashMap operations, **O(n) auxiliary space** in the worst case (distinct keys). The nested while is amortized O(n), not O(n²).

## Common mistakes
- Counting duplicate *occurrences* instead of the number of **types** whose counts are >=2.
- Incrementing the repeated counter on every count increase beyond 1.
- Forgetting the 2→1 decrement during shrinking.
- Treating an empty input as a valid length-0 window; the API specifically returns [-1,-1].
- Updating the answer **before** restoring validity.
- Forgetting tie-breaking or returning an exclusive right endpoint.
- Assuming IDs are nonnegative or small enough for a frequency array.
- Misstating HashMap expected-case versus pathological worst-case behavior.

## Java syntax and CS61B connections
```java
Map<Integer, Integer> freq = new HashMap<>();
int old = freq.getOrDefault(id, 0);
freq.put(id, old + 1);
if (freq.get(id) == 1) freq.remove(id);
```

Connects to CS61B hash tables, `equals`/`hashCode` semantics for keys, and amortized analysis of two monotonic pointers. Compare October 5's weak frequency-map window and October 13's quota window: the *meaning* of the counter differs, but the add/shrink invariant is the same.
