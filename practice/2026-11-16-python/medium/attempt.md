# Attempt — Longest Consensus Segment

Complete **before** viewing reference/.

- Start / finish / total minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal expected time and auxiliary space:
- First failed test / Python syntax issue:
- One recognition cue or mistake to revisit in 2–4 days:

## Sliding-window reasoning

- Why is the necessary number of changes length − largest frequency?
- What does counts[value] mean at every iteration?
- Which condition triggers movement of the left boundary?
- Why does incrementing right and decrementing left each occur at most n times?
- Why can max_seen_frequency be kept nondecreasing?
- Give a concrete window where max_seen_frequency is stale but the best answer remains correct.
- Would a stale maximum still be safe if the problem asked to return an actual edited window and target label?
- Compare this with signed-sum prefix hash maps: why does ordinary sliding-window movement work **here**?
- Why do negative integer labels not matter to the technique?

## CS61B transfer

- Analyze expected hash table operations, including deletion of zero-count keys.
- Name the maintained invariant and distinguish it from the actual feasibility of each current window.
- What input layout would defeat a quadratic scan but not this approach?
