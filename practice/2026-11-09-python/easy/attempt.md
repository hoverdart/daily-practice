# Attempt — Merge Service Windows

Fill out **before** opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time and auxiliary space:
- Optimal time and auxiliary space:
- Tests or hints I needed:

## Recognition and invariant

- Which phrases suggest sorting by one interval endpoint and sweeping?
- What changes when two intervals **touch** rather than strictly overlap?
- What does merged[-1] represent after processing the first k sorted windows?
- Why can no *future* window reconnect a completed merged interval after a strict gap?
- Why do I use max for the end (nested windows)?
- What changes for empty input, identical windows, negative times, or one interval?
- How do I guarantee that original inner lists remain unmodified?

## CS61B / Python

- Why does comparison sorting dominate complexity?
- Why is Python sorted safer here than in-place list.sort()?
- One proof or edge case to revisit later:
