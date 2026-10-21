# Attempt — Longest Low-Collision Window

Fill in before reading `reference/`.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What makes this a contiguous-window problem?
- Why does shrinking a window never *increase* its equal-ID pair count?
- What does an O(n²) enumeration of windows require?

## Two invariants
- What does `freq[x]` mean?
- What does `pairs` count exactly?
- Adding an ID with frequency f contributes how many pairs?
- After decrementing an outgoing ID from f to f-1, how many pairs disappear?
- Why update best only after shrinking to validity?

## Complexity
- Why isn't the nested while loop quadratic?
- Time / auxiliary space:
- Why `long long` for the pair counter?

## Failed tests, hints, C++ syntax
- `unordered_map`, `find`, `erase`, `pair<int,int>`:
- Tie-breaking and half-open boundaries:

## After reference
- One invariant I can explain without notes:
- One CS61B connection:
