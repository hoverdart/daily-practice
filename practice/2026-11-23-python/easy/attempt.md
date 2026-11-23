# Attempt — Closest Repair Hub by Hops

Complete before viewing `reference/`.

- Start / finish / time spent:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Baseline complexity / optimal complexity:
- First failing test or Python API mistake:
- One thing to review in 2–4 days:

## Recognition and invariant

- Why is each link one hop, even if the input order differs?
- Why can every hub start at distance 0 in **one** deque?
- When is a vertex marked as discovered? Why not wait until removal?
- What does `distance[v]` mean after first discovery?
- How does BFS handle disconnected vertices, duplicate hubs, and self-loops?
- How would the solution change for positive, nonuniform edge weights?
- Where do CS61B queue, graph representation, and unweighted shortest-path ideas appear?
