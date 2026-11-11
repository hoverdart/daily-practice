# Attempt — Rerootable Org Chart Queries

Complete **before** reading reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force runtime and memory:
- Optimal runtime and memory:
- First failed test / C++ STL difficulty / hint:

## Graph/tree modeling and proof

- Why do the undirected tree edges remain unchanged when the root moves?
- What is the difference between the parent array under fixed root 0 and under current root r?
- What does up[j][v] represent, including the 0th ancestor of vertex 0?
- Why can depth and parent be computed by BFS or iterative DFS without recursion?
- In ordinary LCA, why must I lift the deeper node first?
- Why is it safe to lift both nodes when their 2^j ancestors differ?
- State the result using the deepest of LCA_0(u,v), LCA_0(u,r), LCA_0(v,r).
- Explain or diagram **why** that deepest node becomes the LCA under root r.
- What happens for n=1, u=v, u=r, v=r, and a very long path tree?
- Why would recomputing parents after every R request time out?

## C++ / CS61B learning

- What syntax builds std::vector<std::vector<int>> adjacency lists?
- Can I write iterative queue/traversal and 2D ancestor-table allocation from memory?
- How does binary lifting relate to doubling and binary search in CS61B?
- One subtle invariant or mistake to space-repeat later:
