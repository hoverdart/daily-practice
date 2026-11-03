# Attempt — Longest Window With Limited Handoff Types

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognize the structure
- What is the difference between counting unique **items** and unique **adjacent directed transitions**?
- Can I give a brute-force algorithm and state its runtime?

## Maintain the invariant
- Precisely: what does `frequency[key]` count in the current window?
- On extending the right boundary, which one new handoff can enter?
- On removing the left item, which one old handoff can leave?
- Why must a key be deleted when its frequency becomes zero?
- Why does the map's number of keys equal the number of distinct handoffs?
- Why is an inner while-loop compatible with total O(n) time?

## Java / CS61B
- How do I represent an ordered pair of *signed* `int` IDs as a unique `long` key?
- Is my returned interval half-open? How are earliest-left ties handled?
- Expected time and worst-case auxiliary space:
- Bugs, hints, and one concept to review next time: