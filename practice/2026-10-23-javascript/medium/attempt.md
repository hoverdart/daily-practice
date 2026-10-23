# Attempt — Shortest Required-Signal Window

Complete before opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- Why is contiguity a sliding-window signal?
- Why do duplicate requirements change the bookkeeping?
- What would enumerating all windows and recounting cost?

## Invariant
- Exactly what does need.get(x) mean? Can it be negative?
- What does missing count: distinct types or individual occurrences?
- On adding x, when should missing decrease?
- On removing y, when should missing increase?
- Why do we shrink **while valid** for a shortest window, unlike longest-valid-window problems?
- How does earliest-start tie breaking work?

## Complexity and JavaScript Map
- Expected time / auxiliary space:
- Difference between Map.has, Map.get, and Map.set:
- Empty requirements, impossible coverage, negative IDs, repeated extras:

## Failed tests / hints / syntax friction

## After reference
- One transferable sliding-window invariant:
- One connection to CS61B hash tables and amortized two-pointer analysis:

