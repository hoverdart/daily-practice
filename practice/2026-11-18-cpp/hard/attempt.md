# Attempt — Critical Firmware Rollout Chains

Complete before reading reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal time and auxiliary space:
- First failed test, counterexample, or C++ compile issue:
- One graph/DP invariant to revisit:

## Recognition and invariants

- Why is the project finish time a **maximum**, not a minimum, over dependency chains?
- What happens if tasks have no incoming edges, no outgoing edges, or zero duration?
- Why must the graph be acyclic for a simple topological DP?
- What does ending[u] mean? What are its initial values?
- What does starting[u] mean? Why iterate topological order in reverse?
- Prove ending[u]+starting[u]-duration[u] is the best path length *through* u.
- Prove ending[u]+starting[v] is the best path length using prerequisite edge (u,v).
- What does "on at least one critical chain" mean in a tie? Why are duplicate input edges classified separately?
- Why do we use long long even though each task duration fits in int?
- Why is iterative Kahn processing safer than deep recursion on a 100,000-task chain?

## CS61B transfer

- Compare longest-path relaxation in a DAG to shortest-path relaxation and Dijkstra; what does the topology guarantee?
- Which path property does BFS solve, and why is BFS not sufficient for these weighted task durations?
- Explain how the two passes resemble DP on trees and prefix/suffix computations.
- Describe an alternative exponential path-enumeration baseline.
