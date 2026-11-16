# Attempt — Farthest Critical Server in a Tree

Write this **before** opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Naive search time / space:
- Optimized DP time / space:
- First failed test or Python recursion/syntax issue:
- One mistake or tree invariant worth revisiting in 2–4 days:

## Graph and reroot reasoning

- Why are n−1 undirected edges enough to guarantee a tree only when connected?
- Why is the route between any two vertices unique?
- What does parent[u] mean? Why must a top-down order precede reverse order?
- Precisely define down[u], up[u], and the −1 sentinel.
- Why is iterative traversal necessary on a 120k-node chain?
- Why does down[u] = max(0 if marked, down[child] + weight) work?
- Why does a child need to exclude **its own** branch from the parent's best candidate?
- How do the largest two distinct-source child contributions solve that exclusion?
- What happens if the two greatest distances are tied?
- Why are zero-weight edges safe with −1 representing unreachable?
- What is up[root], and why?
- Why is answering max(down, up) exhaustive?

## CS61B connections

- What are the similarities to DFS, rooted trees, preorder/postorder, and dynamic programming?
- How does this compare with repeating DFS or Dijkstra from every critical server?
- Could a diameter-endpoint observation offer another linear solution?
