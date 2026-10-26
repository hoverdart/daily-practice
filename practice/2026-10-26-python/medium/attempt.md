# Attempt — Longest Affordable Channel Window

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute-force baseline
- Why is contiguity + nonnegative cost a sliding-window signal?
- Brute-force time (with running sum / channel counts):

## Two invariants
- What does `freq[channel]` represent?
- Why is `len(freq)` exactly the number of distinct channels?
- What does `total` represent?
- Why do I shrink while **either** constraint is violated?
- Why must a zero-frequency channel be deleted from the map?
- When can I update the best answer?
- How is the earliest-start tie handled?

## Claimed time and auxiliary space
- Why isn't the nested `while` loop quadratic?

## Failed tests, hints, Python dict.get/del syntax friction

## After reference
- One sliding-window invariant I can now state from memory:
- One reason the method would fail with negative costs:
- One CS61B hash-table / amortized-analysis connection:
