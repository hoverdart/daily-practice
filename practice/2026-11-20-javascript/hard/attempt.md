# Attempt — Cheapest Route After Reversing One Link

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force complexity:
- Optimal complexity / extra space:
- First failed test or JS heap bug:

## Directed weighted-graph reasoning

- Define forward and reversed adjacency lists exactly.
- What does each of the two Dijkstra distance arrays represent?
- Derive the candidate distance for reversing `u -> v`: why does it start from v and arrive at u?
- Why can a valid route be split into original-graph prefix, reversed edge, original-graph suffix?
- Prove the minimum across all edges and the no-reversal case is globally optimal.
- Why does Dijkstra require **nonnegative** costs?
- State the invariant when the non-stale cheapest heap item is popped.
- Why do you skip stale heap tickets?
- Why must you not force a reversal if the original route is already cheaper?
- What if source equals target, graph is disconnected, weights are zero, or parallel links exist?
- Why do we use `Infinity` and `Number.isFinite`, rather than a small sentinel?

## CS61B transfer

- Compare with standard BFS, 0–1 BFS, and Bellman-Ford.
- Give O((V+E)log V) time and O(V+E) space using lazy-key updates.
- One shortest-path idea I still want to practice:

