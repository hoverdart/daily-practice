# Attempt — Budgeted Long-Cable Network

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Graph recognition
- Why is this a spanning-tree / connectivity problem rather than a shortest path?
- Why does a plain BFS not optimize a weight threshold?
- How would enumerating all spanning trees scale?
- What does a DSU represent after processing only cables with weight <= T?

## Monotone feasibility
- If the cheap-edge graph has c components, why are at least c-1 long cables necessary?
- Assuming the original graph is connected, why are c-1 long cables also sufficient?
- Write the exact feasibility predicate in terms of c and k:
- Why does increasing T never make feasibility worse?
- Binary-search invariant for lo and hi:

## C++ and CS61B
- Path compression and union-by-size invariants:
- How should parallel edges and self-loops behave?
- Why must disconnected graphs return -1, even if k is large?
- What are the answers when n=1, k=0, k=n-1?
- Time / extra space:
- Failed tests / hints / tuple/structured-binding syntax friction:
- One CS61B Kruskal/union-find connection to retain:

