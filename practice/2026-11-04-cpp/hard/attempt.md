# Attempt — Coordinated Relay Rendezvous

Complete this **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime:
- Optimal runtime and auxiliary space:
- One bug, false assumption, or hint I needed:

## Recognition and explanation

- Why is the earliest departure from a hub max(distA[v], distB[v]) rather than their sum?
- Why may the couriers choose independently shortest routes before rendezvous?
- How do I compute dist(v,T) for all v with one Dijkstra run?
- How do unreachable hubs influence the answer, even if one courier can get there?
- Does Dijkstra remain valid with zero-weight roads? What if a road were negative?
- How do I implement a C++ min-priority_queue and ignore stale entries?
- How is the smallest-ID tie broken even when input hub IDs are unsorted?

## Reflection

- Did I prove the invariant, or just recognize the pattern?
- Which CS61B concept was involved?
- One concrete idea to revisit in 2–4 days:
