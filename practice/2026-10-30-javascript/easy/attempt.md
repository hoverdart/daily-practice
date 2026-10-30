# Attempt — Closest Shared Supervisor

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- Why is the reporting structure a rooted **forest** rather than one tree?
- What does a parent pointer let you do without building child adjacency lists?
- What would comparing every pair of ancestors cost?

## Invariant and correctness
- What exactly does the ancestor `Set` contain?
- Why is the **first** ancestor of b that is in the set the *lowest* shared ancestor?
- What happens when a=b, roots differ, or the chain is very deep?

## Complexity / JavaScript
- Time in heights h_a and h_b:
- Auxiliary space:
- `Set.has` expected-time behavior:
- Failed tests / hints / API friction:

## CS61B connection
- Explain parent/edgeTo arrays, rooted trees, and why iterative traversal avoids call-stack limits.
