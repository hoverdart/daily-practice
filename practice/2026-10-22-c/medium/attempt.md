# Attempt — Longest Stable Telemetry Window

Complete **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition / brute force
- Why does a contiguous interval suggest sliding window?
- Why aren't scalar max/min sufficient when left advances?
- Brute-force time complexity:

## Deque invariants
- Which indices are stored in the max deque, and how are their values ordered?
- Why remove indices from the back when a new right endpoint arrives?
- When should a deque front expire?
- Why is the nested shrink loop amortized O(n)?
- How do I preserve earliest-start tie breaking?

## Complexity / C mechanics
- Time / auxiliary space:
- Why cast to long long **before** subtraction?
- How are deque arrays allocated and freed?

## Failed tests / hints / C syntax friction

## After reference: one transferable invariant
