# Attempt — Safest Bottleneck Route Queries

Fill this out **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Repeated-graph-search baseline time / space:
- Optimal preprocessing and per-query time / space:
- First failed test or Java collections issue:
- One graph theorem / invariant to revisit in 2–4 days:

## Recognition signals and proofs

- What does path **maximum edge** mean, compared with shortest **sum**?
- Explain why a path with more hops can have a smaller bottleneck.
- How could modified Dijkstra solve one query without a preprocessing tree?
- What property of a minimum spanning tree makes its u–v path minimax?
- Why is a **forest** needed for disconnected input? What does Kruskal do with self-loops and duplicate edges?
- State the union-find invariant and the benefit of path compression + union by size.
- What must component[u], depth[u], up[k][u], and maxOnJump[k][u] mean?
- Why use iterative BFS rather than recursive DFS on a 100k-node chain?
- How do you lift a deeper node before comparing ancestors?
- Why lift both nodes from highest power to lowest when looking for LCA?
- Where do you include the final two edges into LCA?
- Why may the answer to a same-node query be 0 even if the graph has positive edges?
- How do zero-weight cables and large (1e9) exposures affect sentinel choice and integer types?

## CS61B and Java transfer

- What is the complexity of sorting, union operations, lifting preprocessing, and q queries?
- How do you use Arrays.sort with a Comparator and ArrayDeque for traversal?
- Explain the difference between DSU parents and rooted-tree ancestors.
- What spaced-repetition follow-up would be most useful?

