# Attempt — Alternating-Band Relay Route

Complete before opening `reference/`.

- Started / finished / minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal time and space:
- First failing test / JS syntax issue:
- One mistake to revisit in 2–4 days:

## Reasoning and CS61B links

- Why does arrival lastBand affect future legal moves, even at the same station?
- How does dist[2*u+band] encode a state? Which state may traverse an edge of band b?
- How can either band be the very first edge?
- Why can the first non-stale popped target state be returned?
- State the min-heap parent/child invariant; describe swim/sink operations.
- Why do strict relaxations avoid infinite loops on zero-delay cycles?
- Compare Bellman-Ford on the expanded graph with Dijkstra.
- Explain O((n+m)log(n+m)) runtime with heap duplicates.
- What goes wrong if links are accidentally treated as undirected?

## After solving

- State your algorithm's core invariant without looking.
- What question or skill should the next practice revisit?
