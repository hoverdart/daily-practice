# Attempt — Count the Fastest Dispatch Routes

Complete **before** opening `reference/`.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Graph recognition
- Why weighted Dijkstra rather than BFS, DFS, or MST?
- What is in each adjacency-list entry?
- Why use `long` for distances?

## Brute force → optimal
- What would enumerating every route cost?
- How do I combine distance minimization with route counting?

## Dijkstra invariant
- What does `dist[v]` mean?
- What does `ways[v]` mean?
- What happens on `candidate < dist[v]`?
- What happens on `candidate == dist[v]`?
- Why skip a stale priority-queue entry?
- Why is counting during Dijkstra safe when **all weights > 0**?

## Complexity (n vertices, m edges)

## Failed tests, hints, Java API friction
- `PriorityQueue<long[]>` comparator:
- `ArrayList`, `Arrays.fill`, `Long.compare`, modulo:

## After reference
- One shortest-path invariant I can now explain without notes:
- One future problem that would need expanded graph state:
