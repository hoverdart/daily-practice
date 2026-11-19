# Attempt — Longest Stable Sensor Window

Complete before opening `reference/`.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force and optimal time:
- Extra space:
- C syntax/memory bug or failed case:

## Monotonic deque invariants

- Why is a long **contiguous** range with an upper spread bound a sliding-window signal?
- Why does an ordinary running maximum/minimum break when an extremum leaves the left edge?
- What does each index deque contain, and why does its front identify the correct extreme?
- On inserting the new rightmost reading, which indices get discarded from each deque's **back**?
- On advancing left, which indices get evicted from each deque's **front**?
- Why is `(long long)max - (long long)min` safe for extreme 32-bit values?
- Why does shrinking restore validity without missing any longer answer?
- Why is the nested while loop *amortized* O(n), not O(n²)?
- How do you preserve earliest-start tie breaking?

## CS61B follow-up

- Compare these deques with array-based deques and with a heap (including lazy deletion).
- What one invariant or C array-index issue should recur soon?
