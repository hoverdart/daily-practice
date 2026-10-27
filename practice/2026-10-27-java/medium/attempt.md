# Attempt — Budgeted Distinct Signal Windows

Complete **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- Why do contiguous windows and nonnegative costs suggest two pointers?
- Why is exactly k harder than at most k in one window?
- What would O(n²) enumeration with running sums/counts do?

## Sliding-window invariants
- What does frequency[code] represent?
- Why must I delete zero-frequency keys to make frequency.size() correct?
- Why shrink while **either** the distinct count or the cost is too large?
- After shrinking, why do right-left+1 valid windows end at right?
- Explain exactlyK = atMostK - atMost(K-1), with the same budget in both.

## Java, complexity, reflection
- Why use long for the cost sum and answer?
- What happens with k=0, empty input, and zero-cost events?
- Why is the nested while loop amortized linear?
- Time / auxiliary space:
- Failed tests / hints / HashMap API friction:
- One transferable sliding-window invariant:
