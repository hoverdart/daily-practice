# Attempt — Directional Rail Repairs

Complete before opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- What are the graph's vertices and directed weighted edges?
- Why can an ordinary BFS count of hops give the wrong answer?
- What would a binary-heap Dijkstra implementation cost?
- Which edge-weight restriction makes a deque sufficient?

## 0-1 BFS invariant
- Why put a zero-cost relaxation at the **front** of the deque?
- Why put a one-cost relaxation at the **back**?
- Why is the first nonstale pop of the goal optimal?
- What does `dist[r][c]` mean?
- How do you handle repeated states/stale entries?
- Why is the edge cost based on the **departure** cell?

## Python / CS61B
- Time and space in V=rows×cols and E≈4V:
- `deque.popleft`, `appendleft`, `append` syntax:
- How is 0-1 BFS related to BFS, Dijkstra, and edge relaxation?
- One counterexample to plain BFS:
- Failed tests, hints, and a concept to revisit:
