# Attempt — Which Cables Are True Bridges?

Complete before opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime and space:
- Optimal runtime and space:
- First failed test or C memory issue:

## DFS / correctness

- Give formal meanings for tin[u] and low[u].
- Why is low[child] > tin[parent] sufficient and necessary?
- Simulate a 3-cycle: what are tin and low at the deepest child?
- Simulate two parallel cables between 0 and 1: why must both be non-bridges?
- Why does skipping the parent vertex instead of the parent edge ID fail?
- Why are self-loops never bridges?
- How does cursor[u] allow an iterative DFS to return from a child?
- What happens with disconnected graph and isolated vertices?
- What memory is owned by the caller? What would you free?
- One graph invariant to review in 2–4 days:

