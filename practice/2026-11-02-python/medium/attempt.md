# Attempt — Longest Policy-Compliant Event Window

Complete before opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- Which phrases signal a sliding window with a frequency map?
- What is the cost of trying all O(n²) intervals?
- Why is it safe to move the left pointer forward permanently?

## Precise invariant
- After processing right, what does `freq[x]` count?
- Why can **only the newly inserted event ID** violate its cap?
- What happens when a cap is zero and the event is removed from the map?
- Why use `freq.get(x, 0)` in the shrink condition, not `freq[x]`?
- Why update best only on strictly longer windows?
- Explain why two nested loops still cost O(n) total.

## Python / CS61B
- Expected time / auxiliary space:
- Difference between `dict.get`, `del`, and zero-frequency keys:
- How is this a hash-table + amortized two-pointer invariant?
- Failed tests, hints, and one sentence you want to remember:
