# Medium — Longest Stream with Limited Repeated Types

A monitoring system receives integer event IDs. A **repeated type** is an ID that occurs **at least twice** inside the current contiguous window. You may tolerate at most `k` **different repeated types** in a window. A type appearing three, ten, or one hundred times still contributes **one** repeated type, not its number of extra occurrences.

Return the inclusive endpoints `[left, right]` of the **longest valid nonempty contiguous window**. If multiple windows have the same maximum length, return the one with the **smallest left index**. For an empty stream, return `[-1,-1]`.

Implement:

```java
public static int[] longestLimitedRepeatWindow(int[] events, int k)
```

Examples:
- `events=[4,4,4,9,9,7,7], k=1` → `[0,3]`: `[4,4,4,9]` has only one type with frequency >= 2.
- `events=[1,2,1,2,3], k=1` → `[1,4]`: `[2,1,2,3]` repeats only type 2.
- `events=[2,3,4], k=0` → `[0,2]`.

Constraints: `0 <= events.length <= 100_000`, `0 <= k <= 100_000`, IDs are arbitrary signed integers. Do not modify the input.

**Target:** O(n) expected time and O(n) auxiliary space using `HashMap<Integer,Integer>`. Explicitly describe what happens to the repeated-type counter when a frequency crosses **1 → 2** or **2 → 1**.

A valid window remains valid when elements are removed. How does that monotonic property help?