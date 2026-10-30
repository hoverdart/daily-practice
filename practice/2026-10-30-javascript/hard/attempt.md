# Attempt — Critical Route Count in a DAG

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What does "prerequisites with no cycles" tell you about the graph?
- Why does a DFS enumerating **every** path potentially take exponential time?
- Why are BFS and Dijkstra not the right algorithms for a **longest weighted path with negative edges**?

## Topological DP invariant
- What does `indegree[v]` represent during Kahn's algorithm?
- Why must even unreachable nodes participate in topological processing?
- What do `best[v]` and `ways[v]` mean **after all predecessors are processed**?
- When do you **replace** `ways[v]`, and when do you **add** to it?
- Why is `-Infinity` safer than `0` for unreachable states?
- What happens when start=target? When all routes have negative weight?

## Complexity / JavaScript
- Time in n vertices and m edges:
- Space for adjacency, indegree, queue, best, ways:
- Why is `queue.shift()` risky at 100,000 nodes? What is the head-index alternative?
- Modulo arithmetic and integer safety:
- Failed tests / hints / friction:

## CS61B connections
- Connect topological sort, edge relaxation, and shortest-path dynamic programming on DAGs.
- Why would cycles change the problem fundamentally?
