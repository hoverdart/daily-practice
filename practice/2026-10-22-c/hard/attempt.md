# Attempt — Critical Relay Links

Complete **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition / brute force
- How is a bridge different from a shortest path or MST edge?
- How could I remove each cable and recompute connected components?
- Why is O(m(n+m)) too slow?

## DFS / low-link invariant
- What do tin[u] and low[u] mean?
- Why is (parent,u) critical exactly when low[u] > tin[parent]?
- Why skip the **parent edge ID** instead of the parent vertex?
- What happens with parallel cables, self-loops, disconnected components?
- How does iterative DFS simulate recursive postorder?

## Complexity / C mechanics
- Time / auxiliary space:
- How do head, to, next, edge_id encode adjacency?
- How are partial allocations cleaned up on failure?

## Failed tests / hints / syntax friction

## After reference: one transferable graph invariant
