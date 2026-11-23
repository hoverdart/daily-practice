# Attempt — Maximum Unique Rewards from Start to Exit

Complete before viewing `reference/`.

- Start / finish / total minutes:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Baseline algorithm and complexity:
- Optimal complexity / extra space:
- First failed test / iterative DFS bug / Python syntax issue:
- One concept to revisit in 2–4 days:

## Graph recognition and correctness

- Why is this not an ordinary shortest-path problem? Why does a simple visited set lose valuable routes?
- Why does revisiting a room not collect reward a second time?
- Precisely define **strongly connected component** (SCC).
- Why can we visit *every* room in one SCC and still exit at any designated vertex of that SCC?
- Why does contracting SCCs produce an acyclic graph?
- Describe the first-pass DFS **finish order** and the second pass on reversed edges.
- Why does the iterative `(node, next_edge_index)` stack emulate recursive postorder?
- Define `dp[component]`, including the `-1` unreachable sentinel when rewards may be zero.
- Why is the answer a **maximum** over predecessors, not a sum of branch rewards?
- Why are duplicate inter-component edges harmless when in-degree is counted and decremented consistently?
- How can you do all traversals safely for a 100k-node chain?
- Connect SCCs, DFS, topological sort, and DP to CS61B graph fundamentals.
