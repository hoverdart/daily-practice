# Attempt — Single-Use Transit Voucher

Complete before opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Graph recognition
- Why Dijkstra, not BFS, DFS, Bellman-Ford, or MST?
- Why is a vertex ID alone insufficient as the visited/distance key?
- Draw the two-layer state graph for n=3.

## Brute force → optimal
- What if I enumerated all routes and tried waiving each edge?
- Could I instead run ordinary Dijkstra from both ends and evaluate each voucher edge?
- Why is a **single** Dijkstra over (vertex,used) states also correct?

## Relaxation / heap invariant
- What is dist[2*v+used]?
- What are the two outgoing transitions when used=0?
- Why is a free edge still safe for Dijkstra?
- Why must I skip stale heap entries?
- Why can I return when the first (goal,1) state is popped?
- What happens for start === goal with no edges or with a cycle?

## Complexity / JS mechanics
- State count / transition count / time / auxiliary space:
- How does a binary heap push/pop work?
- Why is an array used as a heap instead of repeatedly sorting a queue?
- Any issues with Infinity, Number precision, directed edges, or parallel edges?

## Failed tests / hints / syntax friction

## After reference
- One invariant I can now explain without notes:
- One CS61B priority-queue/graph-state connection:

