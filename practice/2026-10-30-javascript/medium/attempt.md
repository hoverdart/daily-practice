# Attempt — Longest Recalibratable Signal Run

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What words suggest a sliding window rather than sorting?
- Why is the minimum number of changes in a window `length - modeFrequency`?
- What is the brute-force time with a running frequency map per left endpoint?

## Window invariant
- What does `freq.get(x)` count **right now**?
- When does `maxFreq` increase? Why can it be stale after left moves?
- Why can a stale `maxFreq` still give the correct **global maximum length**?
- Why shrink while `length-maxFreq > k`, and not while `>= k`?
- Why does each pointer advance only O(n) times?

## JavaScript / complexity
- Expected time and auxiliary space:
- `Map.get(x) || 0` and removing zero-frequency keys:
- Edge cases (k=0, k=n, all equal, all distinct, negative IDs):
- Failed tests / hints:

## CS61B connection
- Explain hashing, amortized two-pointer movement, and the distinction between a precise invariant and a safe historical bound.
