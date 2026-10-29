# Attempt — Shortest Distinct-Signal Coverage

Complete before opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- Why does a contiguous segment plus a minimum-length objective suggest a sliding window?
- What would enumeration with a fresh distinct-count table cost?

## Core invariant
- Exactly what does `count[id]` represent?
- When does `distinct` increment/decrement?
- Why do we shrink **while valid**, not while invalid?
- Why is earliest-start tie-breaking preserved by updating only on strictly shorter lengths?
- What happens for `k=0`, `k>256`, impossible coverage, empty input, byte value 255?

## C / complexity
- Time / auxiliary space and amortized proof:
- Failed cases / hints / unsigned-char indexing friction:
- One connection to CS61B hashing and two-pointer analysis:
