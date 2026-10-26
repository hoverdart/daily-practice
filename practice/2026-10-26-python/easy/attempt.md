# Attempt — First Sufficient Cache Slot

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- Why is this a binary-search problem rather than a hash-set lookup?
- Cost of scanning all slots for every request:

## Lower-bound invariant
- What is ruled out strictly to the left of `lo`?
- What remains possible at and to the right of `hi`?
- Why is `hi = mid` correct when `capacities[mid] == target`?
- How do empty arrays, duplicate values, and a missing answer behave?

## Claimed time and auxiliary space

## Failed cases, hints, and Python syntax friction

## After reference
- One off-by-one rule to remember:
- One connection to CS61B binary search / ordered data structures:
