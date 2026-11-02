# Explanation — Longest Policy-Compliant Event Window

## Recognition signals
A **contiguous** longest segment with **upper bounds on window-local counts** is a sliding-window problem. Unlike a single bound on the number of distinct values, each event ID has its own capacity. This is a fresh frequency-map invariant, not a global histogram.

## Brute force versus optimal
Enumerate all O(n²) intervals and track a dictionary of counts for each starting index. Rechecking every key each time could make the baseline cubic; an optimized brute-force approach can maintain a violation count and remain O(n²).

For the optimal solution, expand right one event at a time. Before insertion, every cap is satisfied. Inserting ID x changes only `freq[x]`, so only x can violate a cap. Shrink from the left **while x is over its cap**. The window is then valid. Update the longest half-open interval, but only when strictly longer to preserve earliest-start tie-breaking.

## Invariant and correctness
After each outer iteration, `freq` equals the multiplicities in `events[left:right+1]`, and each count is within its cap. Every window starting before `left` and ending at `right` is invalid: removing fewer items would leave x above its cap. Thus the current window is the longest valid one ending at right. Taking the best over all right endpoints yields the global optimum. On ties, earlier left endpoints are discovered no later than later ones, and strict updates preserve the earliest.

**Important cap=0 trap:** when the incoming x has cap zero, shrinking can remove x itself, deleting its key. The while condition must use `freq.get(x, 0)` rather than `freq[x]` to avoid KeyError. The valid window may become empty.

## Complexity
Each event enters the right side once and leaves the left side at most once: **O(n) expected time**, despite the nested loop. Dictionary storage is O(d), where d is the number of distinct IDs in the current window, plus O(1) scalar state. Input dictionaries are not mutated. Hash-table worst-case behavior is excluded from expected-time analysis.

## Common mistakes
- Counting occurrences over the entire array rather than inside the window.
- Forgetting to decrement/remove the departing ID.
- Treating an absent cap as zero instead of one.
- Stopping after one left shift even if the new ID is still over its cap.
- Crashing when the incoming event has cap zero.
- Updating on equal length and losing earliest-start tie-breaking.

## CS61B connections
Hash maps and expected constant-time lookup; amortized analysis of two monotone pointers; loop invariants; a special case of maintaining feasibility under incremental updates. This explicitly revisits the weak frequency-dictionary bookkeeping observed in the earlier sliding-window attempt.