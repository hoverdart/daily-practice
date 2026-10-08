# Medium Reference Notes — Minimum Audit Window

**Read after attempting the problem.**

## Recognition signals

"Shortest contiguous segment containing every required kind" => **minimum covering sliding window**. This differs from the previous "longest window with at most K distinct" problem, but uses the same idea: a frequency structure lets you remove the leftmost item in O(1).

## Brute force

Try each start index and extend right until all requirements are present, keeping the shortest. Worst-case O(n² + 256) time with a fixed-size count array, or worse if checking the entire window each time.

## Optimal invariant

`needed[code]` records membership in the distinct requirement set. `freq[code]` records how many occurrences of that required code are currently in `events[left..right]`. `missing` counts the number of **distinct required codes with frequency zero**.

1. Initialize `needed` and `missing`, ignoring duplicate required codes.
2. Advance `right`. If its required code goes from frequency 0 to 1, decrement `missing`.
3. While `missing==0`, the window is valid: record it if shorter, then remove `events[left]` and advance `left`. If a required frequency falls to 0, increment `missing` and stop shrinking.
4. Keep the first minimum-length window by updating only for **strictly shorter** lengths; left increases monotonically, so ties naturally retain earliest start.

Pseudo:

    for right in [0,n):
      add events[right]
      while missing == 0:
        update best if strictly shorter
        remove events[left]
        left++

## Why the counts matter

A boolean "seen" flag alone cannot tell whether removing a code from the left makes it absent: the same code may appear again later in the window. The frequency array solves that exact issue. This directly revisits the confusion noted in the October 5 attempt log.

## Complexity

Each pointer moves forward at most n times. The inner while loop is therefore **amortized O(n) total**, not O(n²). Initialization is O(required_count + 256); extra space O(256).

## Edge cases and C traps

- If no codes are required, answer is empty window at start 0.
- If a required code never appears, answer -1/start -1.
- Required list may repeat codes: do not count duplicates twice.
- Tie-break earliest start, not earliest end.
- Indexing `needed[code]` is safe only because the input contract guarantees codes in 0..255.
- The `events` pointer can be NULL when `n==0`; the loop must not dereference it.
- Do not decrement frequencies for non-required codes unless you intentionally track all codes.

## CS61B connection

Direct-address arrays are a special case of maps: when the key universe is tiny, they beat hashing on simplicity and constants. Two-pointer amortized reasoning is similar to resizing and deque amortization.

## Next time, recognize

**At-most constraint** => shrink when invalid; **minimum covering constraint** => shrink while valid.
