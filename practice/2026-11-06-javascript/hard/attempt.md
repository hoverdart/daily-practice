# Attempt — Cheapest Compliant Deployment Order

Complete this *before* reading reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal time and space:
- Failed tests or hints:

## Graph/DP recognition

- How do prerequisite pairs define a directed graph?
- Why does an ordinary topological sort not minimize switching cost?
- What is the state dp[mask][last] and what does each dimension encode?
- Why can I deploy next only when all its prerequisite bits are already set?
- How do I handle the first module (no previous module)?
- Explain the invariant after processing masks in increasing numeric order.
- Why does the transition always lead to a larger mask?
- Why is the graph of DP states acyclic even if prerequisites have a cycle?
- What result tells me the original prerequisite graph was cyclic?
- Why is a greedy nearest-switch approach wrong? Invent a counterexample.
- Why does bitwise arithmetic work with n <= 15 in JavaScript?

## CS61B / review

- Which CS61B concepts appear (DAG, topo order, dynamic programming, array indexing)?
- Could I have used memoization instead of bottom-up DP?
- Why is the cost matrix potentially asymmetric?
- Which correctness proof or invariant would I explain in an interview?
- One concept to revisit in 2–4 days:
