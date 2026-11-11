# Attempt — Longest Trace With Limited Repeated Handoffs

Complete **before** reading reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime / space:
- Optimal expected runtime / space:
- First failed test or C++ syntax problem:

## Sliding-window recognition and invariants

- Why are the station visits the window elements but the **adjacent pairs** the counted objects?
- Why are handoffs (a,b) and (b,a) equal? What about (a,a)?
- What is the invariant for freq[handoff] and for total repeats?
- When adding an already-seen pair, why does repeats grow by exactly one?
- When deleting a pair with frequency 1, why does repeats **not** shrink?
- When deleting a pair with frequency 2 or more, why does repeats shrink by one?
- Which exact edge vanishes when left becomes left+1?
- Why does shrinking never discard a candidate that could improve later?
- How do I handle n=0, n=1, repeated IDs, signed extremes, and ties?
- Why is an inner while loop compatible with total O(n) progress?

## C++ and CS61B transfer

- How does unordered_map differ from Java HashMap in syntax and guarantees?
- How can a signed pair be encoded without relying on concatenated strings?
- Can I state the expected-versus-worst-case qualification for hashing?
- One invariant or bug worth revisiting in 2–4 days:
