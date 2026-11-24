# Attempt — Longest Quiet Block

Complete before opening reference/.

- Start / finish / minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Brute force / optimal complexity:
- First failing test or Java Map mistake:
- One thing to revisit in 2–4 days:

## Window invariants
- Write the conflict count as a sum over frequencies.
- If the incoming ID already has frequency f, how many pairs appear? Why?
- If an outgoing ID has frequency f before deletion, how many pairs disappear?
- Why can a left boundary once discarded never be optimal for any later right boundary?
- Why shrink with while, not if, and not reset the whole window?
- What is the distinction between a repeated ID, a repeated occurrence, and an equal pair?
- Why does a long matter even if all IDs fit in an int?
- Which CS61B map and amortized-analysis concepts apply?
