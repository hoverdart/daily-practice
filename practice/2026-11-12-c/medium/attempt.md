# Attempt — Longest Drift-Controlled Span

Complete before opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime and space:
- Optimal runtime and space:
- First failed case or C bug:

## Sliding-window reasoning

- Define the exact edge set summarized by drift.
- On extending right, which edge enters?
- On advancing left, which edge exits?
- Prove the earliest feasible left is optimal for a fixed right.
- Prove the earliest feasible left cannot move backward when right grows.
- Why is an inner while loop still O(n) in total?
- What happens with INT_MIN/INT_MAX, budget=0, all equal readings, and n=0?
- How did I preserve earliest-start tie breaking?
- One invariant or mistake to review in 2–4 days:

