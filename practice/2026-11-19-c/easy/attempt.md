# Attempt — Solo Alerts in a Sorted Chain

Fill out before viewing `reference/`.

- Start / finish / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force and optimal runtime:
- Optimal additional space:
- First test failure / C pointer or allocation mistake:

## Explain the invariant

- Why does a **sorted** input let you classify duplicates by examining contiguous runs?
- What does `tail` represent after processing a run?
- What happens when the first run is repeated? The last run?
- When do you save `next` before calling `free`?
- How do you avoid dereferencing removed nodes?
- Why is the local sentinel safe even though its address must never escape?
- Would removing just the extra duplicates satisfy the problem? Why not?
- How does this relate to CS61B sentinel linked lists and ownership?

## For the next review

- One edge case I missed:
- One ownership/aliasing rule I will apply next time:
