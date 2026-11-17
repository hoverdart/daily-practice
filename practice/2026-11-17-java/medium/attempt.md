# Attempt — Longest Fair Worker Session

Complete **before** looking at reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute force time and space:
- Expected optimal time and auxiliary space:
- First failed test / Java syntax issue / hint:
- One sliding-window invariant to revisit in 2–4 days:

## Window recognition and invariants

- Why does **contiguous** suggest a sliding window?
- What exactly does frequency[id] count? What happens when it becomes zero?
- Why is the only possible new cap violation the ID at right?
- Why does removing from the left always help an upper frequency cap?
- Why does removing from the left **not** help satisfy a minimum distinct-ID count?
- Explain why, for a fixed right, the earliest cap-valid left is the longest candidate.
- Why is checking distinct count only after cap repair sufficient?
- Can you prove a shorter suffix cannot pass minDistinct if the maximal window fails?
- How many times can each pointer move over the whole execution?
- How do empty input, minDistinct=0, negative worker IDs, and equal-length ties behave?

## CS61B / Java connections

- Explain HashMap getOrDefault, put, remove, size, and expected-time guarantees.
- Compare this to the previous frequency-map window exercises: what is the new invariant?
- Describe a counterexample to "shrink while count < minDistinct".
- What should the next practice set reinforce?

