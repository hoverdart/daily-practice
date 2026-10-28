# Attempt — Kth Strongest Calibration Pulse

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- Why does a stream of values plus a small k suggest a fixed-size heap?
- How would sorting everything solve it, and what would that cost?
- What does the root of a **min**-heap of the k strongest values represent?

## Invariant and correctness
- After processing i readings, exactly which readings are in the heap?
- Why can I discard a new reading smaller than the root?
- Why do equal amplitudes count multiple times?
- What changes when k=1 or k=n?

## C++17 and CS61B
- Write the `std::priority_queue` min-heap type from memory:
- Difference between `top()`, `push()`, and `pop()`:
- Claimed time and extra space:
- Tests that failed / hints / syntax friction:
- One CS61B binary-heap invariant to retain:

