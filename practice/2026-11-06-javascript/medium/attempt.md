# Attempt — Exactly K Signal Collision Pairs

Fill out before opening reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force complexity:
- Optimal complexity:
- Tests that tripped me up:

## Frequency-map + sliding-window invariant

- What does freq.get(x) represent at every step?
- Why does adding x introduce exactly freq[x] *new pairs*?
- Why does removing y destroy exactly freq[y]-1 pairs?
- Why does atMost(k) - atMost(k-1) count exactly k?
- Why must atMost(-1) be 0, especially for k=0?
- For each right endpoint, how many legal left endpoints remain?
- Prove that moving left forward never hides a valid future interval.
- Why do the two nested loops still make O(n) progress overall?
- Why does Number arithmetic remain exact under the specified n bound?

## CS61B / JavaScript

- When do I use Map.get, Map.set, and Map.delete?
- Explain hash table expected O(1) lookup vs worst-case caveats.
- One concrete invariant or bug to revisit in 2–4 days:
