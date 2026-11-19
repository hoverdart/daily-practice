# Attempt — Fewest Turns for a Grid Relay

Complete before revealing `reference/`.

- Start / finish / minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- O(rows × cols) target time and space, justified:
- First failed test / C deque memory bug:
- One shortest-path invariant to revisit soon:

## Graph recognition

- If the cost is **turns**, why is ordinary BFS by number of steps wrong?
- Why is the state `(row,col,last_direction)`, rather than just the cell?
- Why do four initial direction states at cost zero make the first move free?
- Why does a same-direction edge cost zero and a changed-direction edge cost one?
- What makes this a **0–1 BFS** rather than Dijkstra or multi-source ordinary BFS?
- Describe the deque-order invariant; why push **front** on zero and **back** on one?
- Why check the ticket's stored distance against `dist[state]` when popping?
- Why is a fixed deque of only `rows*cols` entries unsafe if improved states are re-enqueued?
- Compare O(V+E) with a binary-heap Dijkstra O((V+E)log V), noting `V=4RC` and `E<=4V`.
- Why does a blocked destination or a 1×1 grid need special attention?
- Which of the allocated queue/data arrays owns heap memory, and how is it freed?

## CS61B follow-up

- Give an unrelated “secret state-space graph” example.
- One thing to memorize about shortest-path algorithm selection:
